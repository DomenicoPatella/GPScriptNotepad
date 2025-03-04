#include "Script.h"

const std::string global_script =
R"(
/******************************************************
//
// Global Script
// 
******************************************************/

Initialization
	
	Print("Global script ")
	
End

// Indicates that all rackspaces and songs have been loaded
On SystemEvent matching Gigloaded
	Print (" Gig is loaded..")
	Notify("Gig is loaded..")
End


// Indicate that the playhead has been started (1.0) or stopped (0.0)
On SystemEvent(newValue : double) matching PlayheadStateChanged 
	var x: integer
	Print("Playhead value ->" + newValue)
	x= Ceiling(newValue)
	Notify("Playhead value ->" + x)
	
End


//Indicate that the global transpose changed
On SystemEvent(newValue : integer) matching GlobalTransposeChanged
	Print ("Transpose ->" + newValue) 
	Notify("Transpose value ->" + newValue)
End


//Call every time the beat is changed
On BeatChanged(barNumber : Integer , BeatNumber : Integer)
	Print ("BeatChanged Bar -> " + barNumber)
	Print ("BeatChanged BeatNumber -> " + BeatNumber)
	
End

// This callback should generally be used instead of the On BeatChanged callback,
On Timeline
	Prolog
		Print("PRolog :This optional code gets executed before the code for the specific beat is triggered")
	End 
	1:1
	Print("Timeline Playhead just started")
	2:2
	Print("Timeline We are at bar 2 beat 2")
	
	84:3
	//Print("-- we are a long way into the timeline now")
	Epilog
		Print("Epilog :This optional code gets executed after the code for the specific beat is triggered")
	End
End

)";
