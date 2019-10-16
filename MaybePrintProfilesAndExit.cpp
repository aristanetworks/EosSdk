// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.
// +build ignore

// To facilitate the making of customized sysdb-mount-profiles (in place of the
// brute-force one "EosSdk", see /usr/lib/SysdbMountProfiles/EosSdkAll), an app can
// be started with the env var EOS_PRINT_PROFILES_AND_EXIT pointing to a filename
// where the profile should be written, then exit.
// We are not printing directly (prevents dups, agent name is only known late, some
// debug prints might interfere) so we first insert the profiles into a map.
// The collections of utilities we need for that purposes are defined here, under a
// static class in order not to overly pollute the eos space. They are declared in
// eos/inline/sdk.h.
//
// This code is included as a header file into both sdk.cpp and stubs/sdk.cpp

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Initialize static class variables
FILE* print_profiles::print_profiles_fp = 0; // if and where to print
const char* print_profiles::eossdk_progname = 0;
std::map<std::string, bool> print_profiles::profiles_to_print;

// Called in sdk ctor to figure out if recording of managers is needed, if so
// open the target file (its file-pointer will be used later to determine if we
// need to record). The sdk ctor has some complex logic to figure out the agent-name;
// we need that agent-name later when we print the profiles, so it is passed in here.
// (the agent-name is the basename of the executable, unless the AGENT_PROCESS_NAME
// env var is set, in which case it may actually be wrong -- we need basename(exe)).
void print_profiles::set_print_profiles(const char* name) {
   if (getenv("EOS_PRINT_PROFILES_AND_EXIT")) {
      print_profiles_fp = fopen(getenv("EOS_PRINT_PROFILES_AND_EXIT"), "w");
      if (!print_profiles_fp) {
         const char* text =
                    "Error: EOS_PRINT_PROFILES_AND_EXIT must be a writtable file\n";
         fprintf(stderr, "%s", text);
         exit(1); // r+2 because of warnings: discarded fprintf rcode + unused var
      }
      eossdk_progname = name;
   } else {
      print_profiles_fp = 0;
   }
}

// called from xxx_mgr_get() to record that this manager is used
void print_profiles::add_profile(const char * profile) {
   if (print_profiles_fp) {
      profiles_to_print[profile] = true;
   }
}

// called from main_loop() or get_event_loop(): at that point all managers must
// have been instantiated, so print the collected profiles and exit.
void print_profiles::write_profiles() {
   if (print_profiles_fp) {
      if (eossdk_progname) {
         fprintf(print_profiles_fp, "agentName:%s-%%sliceId\n", eossdk_progname);
      } else {
         // extern const char *__progname; would be to GNU specific...
         char myExe[1000];
         if (readlink("/proc/self/exe", myExe, 1000) != -1) {
            fprintf(print_profiles_fp, "agentName:%s\n", basename(myExe));
         } else {
            const char* text =
                 "Warning: couldn't figure out agent name, edit 'TBD' in profile\n";
            fprintf(stderr, "%s", text);
            fprintf(print_profiles_fp, "agentName:!!!TBD!!!\n");
         }
      }
      for (std::map<std::string, bool>::iterator it = profiles_to_print.begin();
           it != profiles_to_print.end(); it++) {
         fprintf(print_profiles_fp, "Include: EosSdk_%s.include\n",
                                     it->first.c_str());
         // BUG206337: Workaround lack of recursive include support in
         // SysdbMountProfiles
         if (strcmp(it->first.c_str(), "IntfMgrHelper") == 0) {
            fprintf(print_profiles_fp, "Include: AgentPlugin-IntfCollections-*\n" );
         } else if (strcmp(it->first.c_str(), "mlag")) {
            fprintf(print_profiles_fp, "Include: MlagStatus-include\n");
         }
      }
      fclose(print_profiles_fp);
      exit(0);
   }
}
