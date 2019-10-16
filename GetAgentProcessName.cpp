// Copyright (c) 2016 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.
// +build ignore

// Note: the AGENT_PROCESS_NAME scheme, outside of our test code, is completely
// obsolete (users cannot set it).
void agent_name_not_found_exit(const char * msg) {
   fprintf(stderr, "We get the agent name from the binary name, or it can be set"
                   "explicitely via the eos::sdk(std::string) constructor.\n");
   fprintf(stderr, "%s.\n", msg);
   fprintf(stderr, "Unable to find a process name: aborting!\n");
   assert(0);
}

std::string get_agent_process_name(void) {

   std::string program_name;

   char * agent_process_name = getenv("AGENT_PROCESS_NAME");
   if (agent_process_name && !strlen(agent_process_name)) {
      fprintf(stderr, "not using AGENT_PROCESS_NAME since empty");
      agent_process_name = 0;
   }

   if (agent_process_name) {
      program_name = agent_process_name;
      size_t i = program_name.find_last_of("-");
      if (i != std::string::npos && i != program_name.size()-1) {
         std::string tmp = program_name.substr(i+1);
         program_name = tmp;
      }
   } else {
      // No name set via the environment variable. Let's use the name
      // from /proc/self/cmdline
      std::ifstream proc_cmdline("/proc/self/cmdline", std::ifstream::binary);
      if (!proc_cmdline.is_open()) {
         agent_name_not_found_exit("Unable to read /proc/self/cmdline");
      }
      int buflen = 200;
      char * cmdline = new char[buflen];
      proc_cmdline.read(cmdline, buflen);
      std::streamsize bytes_read = proc_cmdline.gcount();
      if (!bytes_read) {
         // According to proc(5) this will be 0 for zombies.
         // At this point, we could fallback to readlink on
         // /proc/self/exe, but it isnt' worth the effort at this
         // time.
         agent_name_not_found_exit("Unable to determine an agent name from cmdline");
      }
      std::string line(cmdline, bytes_read);
      delete[] cmdline;

      std::size_t arg_break = line.find_first_of('\0');
      std::string arg0 = line.substr(0, arg_break);
      // Strip off the path
      program_name = arg0.substr(arg0.find_last_of('/') + 1);
      if(program_name == "python") {
         // Running a python agent (i.e. 'python xxx.py' or '/usr/bin/python xxx.py')
         arg0 = line.substr(arg_break + 1, line.find_first_of('\0', arg_break + 1));
         program_name = arg0.substr(arg0.find_last_of('/') + 1);
      }
      // Strip any file extension, i.e. ".py":
      std::size_t last_period = program_name.find_last_of('.');
      if (last_period > 0) {
         // There is at least one character before the "."
         program_name = program_name.substr(0, last_period);
      }

      // now that we are not using the default profile, the libtool wrapper creates
      // naming issues: cut the libtool "lt-" appendage away in the agent name
      if (program_name.compare(0, 3, "lt-", 3) == 0) {
         program_name = program_name.substr(3);
      }

      if (program_name.empty()) {
         char* msg = 0;
         int l = asprintf(&msg, "No agent name found: '%s'", line.c_str());
         if (l<0) {
            msg=(char*)"No agent name, no memory";
         }
         agent_name_not_found_exit(msg);
      }

   }

   // Replace any unsupported characters with '_'
   for (std::string::iterator iter = program_name.begin();
        iter < program_name.end(); iter++) {
      if(!isalnum(*iter) && *iter != '-' && *iter != '_' && *iter != 0) {
         program_name.replace(iter, iter + 1, "_");
      }
   }
   return program_name;
}
