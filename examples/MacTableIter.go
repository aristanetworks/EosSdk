// Copyright (c) 2019 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.
package main

import (
	"eossdk"
	"fmt"
)

// agent is a representation of Mac agent
type agent struct {
	mgr    eossdk.AgentMgr
	macMgr eossdk.MacTableMgr
	tracer eossdk.Tracer
}

// On_initialized intializes the agent options
func (a agent) On_initialized() {
	a.tracer.Trace0("Initializing...")
	defer a.tracer.Trace0("Initialized")
	name := a.mgr.Agent_option("name")
	if name == "" {
		a.mgr.Status_set("greeting", "Welcome! What is your name?")
	} else {
		a.On_agent_option("name", name)
	}
}

// On_agent_enabled is called when the agent is enabled or disabled via the config
func (a agent) On_agent_enabled(enabled bool) {
	if !enabled {
		a.tracer.Trace0("Shutting down")
		a.mgr.Status_set("greeting", "Adios!")
		a.mgr.Agent_shutdown_complete_is(true)
	}
}

// wrapper around mac_table iterator to simplify for caller
func maciter(it eossdk.MacTableStatusIter) chan eossdk.MacKey {
	// caller needs to close chan when breaking from loop
	ch := make(chan eossdk.MacKey)
	go func() {
		for k := it.Next(); !k.IsEmpty(); k = it.Next() {
			ch <- k
		}
		close(ch)
	}()
	return ch
}

// On_agent_option is the callback handler when agent options have been modified
// Available keys are:
// name: Sets the greeting's status to a given value.
// mac: Prints the mac table entries.
// set : Sets the mac table entries to some hard coded values.
// clear: Clears the mac table entries.
func (a agent) On_agent_option(key string, val string) {
	if key == "name" {
		if val == "" {
			a.tracer.Trace3("Name deleted")
			a.mgr.Status_set("greeting", "Goodbye!")
		} else {
			a.tracer.Trace3(fmt.Sprintf("Saying hi to %s", val))
			a.mgr.Status_set("greeting", fmt.Sprintf("Hello %s!", val))
		}
	}
	// for iterators, we break on the empty value of the iter
	for x := a.mgr.Agent_option_iter(); ; {
		foo := x.Next()
		if foo == "" {
			break
		}
		a.tracer.Trace4(foo)
	}

	fmt.Println("mac iter:\n")
	var listokeys []eossdk.MacKey
	if key == "mac" {
		it := a.macMgr.Mac_table_status_iter()
		fmt.Printf("it is %v, %+v, %#v, %T\n", it, it, it, it)
		for k := it.Next(); !k.IsEmpty(); k = it.Next() {
			fmt.Printf("it is %v, %+v, %#v, %T\n", it, it, it, it)
			fmt.Printf("k is %v, %+v, %#v, %T\n", k, k, k, k)
			fmt.Println(k.To_string())

			a.tracer.Trace0(k.To_string())
			a.mgr.Status_set(k.To_string(), a.macMgr.Mac_entry_status(k).To_string())
			listokeys = append(listokeys, k)
			fmt.Println()
		}
	}

	if key == "set" {
		// program some mac entries
		a.macMgr.Mac_entry_set(eossdk.NewMacEntry(
			eossdk.NewMacKey(uint16(1), eossdk.NewEthAddr("0000.1111.2222")),
			eossdk.NewIntfId("Ethernet1")))
		a.macMgr.Mac_entry_set(eossdk.NewMacEntry(
			eossdk.NewMacKey(uint16(1), eossdk.NewEthAddr("0000.1111.2221")),
			eossdk.NewIntfId("Ethernet1")))
		a.macMgr.Mac_entry_set(eossdk.NewMacEntry(
			eossdk.NewMacKey(uint16(1), eossdk.NewEthAddr("0000.1111.2222")),
			eossdk.NewIntfId("Ethernet1")))
	}

	if key == "clear" {
		it := a.macMgr.Mac_table_status_iter()
		for k := it.Next(); !k.IsEmpty(); k = it.Next() {
			a.tracer.Trace0(fmt.Sprintf("del %s:", k.To_string()))
			a.macMgr.Mac_entry_del(k)
		}
		a.tracer.Trace0("mac entries cleared")
	}

	fmt.Println("listokeys:")
	for _, x := range listokeys {
		fmt.Println(x.To_string())
	}

}

// On_mac_entry_set
func (a agent) On_mac_entry_set(entry eossdk.MacEntry) {
	a.tracer.Trace4(fmt.Sprintf("mac entry added %s", entry.To_string()))
}

// NewAgent creates a new agent instance and returns the value of it.
func NewAgent(sdk eossdk.Sdk) agent {
	// Get mgr
	mgr := sdk.Get_agent_mgr()
	macMgr := sdk.Get_mac_table_mgr()
	// Create tracer
	tracer := eossdk.NewTracer("GoAgent")
	agt := agent{mgr: mgr, macMgr: macMgr, tracer: tracer}
	defer tracer.Trace0("Go agent constructed")
	// initialize handler
	_ = eossdk.NewDirectorAgent_handler(agt, mgr)
	macHandler := eossdk.NewDirectorMac_table_handler(agt, macMgr)
	macHandler.Watch_all_mac_entries(true)

	return agt
}

func main() {
	sdk := eossdk.NewSdk()
	name := sdk.Name()
	fmt.Printf("daemon name is %s\n", name)

	argv := "MacTableIter"
	_ = NewAgent(sdk)

	sdk.Main_loop(1, &argv)
}
