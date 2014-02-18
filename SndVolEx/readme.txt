May 31, 2003
- added JPG support
- new CREAM theme
- add placement to themes

May 11, 2003
- Add splash screen with date checking
- registration dialog

- Write a new skin
- Write help file
- about bawx
- portal to eula.txt
- order.txt


May 7, 2003
* Rebrand
* Add product name to the window title bar
* Make CCLib statically linked
* Window is resized correctly no matter what now

May 4, 2003
* Fixed a bug where if mixerGetLineControls failed in CMixerDestination::EnsureInitialized, no "connected" lines would be found.


=====================================================
* Sometimes those pot controls don't appear
* Meaningful error codes
* Saving / Loading
* Double-buffer those pot controls
* Advanced view should persist.
* Sizing issue when bringing up the common dialog twice.
* Command line.
* Drag/drop XML
* Display properties
* Edit box on the about box is foed
* Level monitor
* Recent file list.
* Keyboard accelerators
* Meter window doesnt' support >1 sound card.
* Make ESC work!
* Error checking and reporting.
* Skinning - Add the new super krad window.

- Fix up the UI
- Installer
- Website
- TESTING!

o Fade/Balance for >2 speakers
o Fade control.
o Fix any possible memory leaks related to XML
o Advanced view is kinda ugly - too tall.

o Sound card properties
o Snap-to for the balance controls.


sndvolex -m 0 -d 1 -o "file"

-----------------------------------------------------------------------
SndVolEx (c) 2002 Carl Corcoran
Command line options:

SndVolEx.exe [-m MixerID] [-s SetID] [-o File] [-x]

MixerID - Device ID.  This represents the zero-based index of the
          sound card for which you wish to display properties.
          The first sound card on the system is represented by 0.
SetID   - Control set number.  Typically, 0 represents the
          "Volume Control" and 1 represents the "Recording Control"
File    - The name of a file to import configuration from.
          This must be a file that was exported from SndVolEx.
x       - Specifies that SndVolEx should not display any
          user-interface, but should apply the settings and
          exit immediately.  This is typically used in conjunction
          with -o.

Examples:

SndVolEx.exe -o "c:\settings.xml" -x
Imports the system's mixer configuration from c:\settings.xml and
exits immediately.

SndVolEx.exe -m 1 -s 0
Starts SndVolEx and displays settings for the second sound card
installed on the system, and displays wave-out controls for it.
