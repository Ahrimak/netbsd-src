#include "msg_defs.h"
const char *msg_list[] = {
NULL,
"Installation messages in English","en_US.ISO8859-1","Out of memory!","Yes","No","All","Some","None","none","OK","ok","On","Off","unchanged","Delete?","install","reinstall sets for","upgrade","NetBSD/amd64 10.99.10\n"
"\n"
"This menu-driven tool is designed to help you install NetBSD to a hard\n"
"disk, or upgrade an existing NetBSD system, with a minimum of work. \n"
"In the following menus type the reference letter (a, b, c, ...) to\n"
"select an item, or type CTRL+N/CTRL+P to select the next/previous item. \n"
"The arrow keys and Page-up/Page-down may also work. \n"
"Activate the current selection from the menu by typing the enter key.\n"
"","Thank you for using NetBSD!\n"
"","You have chosen to install NetBSD on your hard disk.  This will change\n"
"information on your hard disk.  You should have made a full backup\n"
"before this procedure!  This procedure will do the following things:\n"
"	a) Partition your disk\n"
"	b) Create new BSD file systems\n"
"	c) Load and install distribution sets\n"
"	d) Some initial system configuration\n"
"\n"
"(After you enter the partition information but before your disk is\n"
"changed, you will have the opportunity to quit this procedure.)\n"
"\n"
"Shall we continue?\n"
"","Ok, let's upgrade NetBSD on your hard disk.  As always, this will\n"
"change information on your hard disk.  You should have made a full backup\n"
"before this procedure!  Do you really want to upgrade NetBSD?\n"
"(This is your last warning before this procedure starts modifying your\n"
"disks.)\n"
"","Ok, let's unpack the NetBSD distribution sets to a bootable hard disk.\n"
"This procedure just fetches and unpacks sets onto a pre-partitioned\n"
"bootable disk.  It does not label disks, upgrade bootblocks, or save\n"
"any existing configuration info.  (Quit and choose `install' or\n"
"`upgrade' if you want those options.)  You should have already done an\n"
"`install' or `upgrade' before starting this procedure!\n"
"\n"
"Do you really want to reinstall NetBSD distribution sets?\n"
"(This is your last warning before this procedure starts modifying your\n"
"disks.)\n"
"","Mounting %s failed.  Continue?\n"
"","I can not find any hard disks for use by NetBSD.  You will be\n"
"returned to the original menu.\n"
"","I found only one disk, %s. \n"
"Therefore I assume you want to %s NetBSD on it.\n"
"","On which disk do you want to %s NetBSD? ","Available disks","Existing \"wedges\"","heads","sectors","mount point (or '-')","cyl","sec","MB","GB","You can use a simple editor to set the sizes of the NetBSD partitions,\n"
"or apply the default partition sizes and contents.","If you do not want to use the existing partitions, you can\n"
"use a simple editor to set the sizes of the NetBSD partitions,\n"
"or remove existing ones and apply the default partition sizes.","\n"
"\n"
"You will then be given the opportunity to change any of the partition\n"
"details.\n"
"\n"
"The NetBSD (or free) part of your disk ($0) is $3.\n"
"\n"
"A full installation requires at least $4 without X and\n"
"at least $5 if the X sets are included.","Choosing mega- or gigabytes will give partition sizes close\n"
"to your choice, but aligned to cylinder boundaries.\n"
"Choosing sectors will allow you to more accurately specify\n"
"the sizes. On most disks, there is little to gain from\n"
"cylinder alignment.  On very old disks, it is most efficient\n"
"to choose partition sizes that are exact multiples of your actual\n"
"cylinder size.\n"
"\n"
"Choose your size specifier","You can now change the sizes for the system partitions.  The default is\n"
"to allocate all the space to the root file system.  However, you may wish\n"
"to have separate /usr (additional system files), /var (log files etc)\n"
"or /home (users' home directories) file systems.\n"
"\n"
"Free space will be added to the partition marked with a '+'.","Other markers: $0 partition.","'=' existing","'@' external","Size","Filesystem","Mount point?","Size for %s in %s?","Change input units (sectors/cylinders/MB/GB)","NetBSD partition","Whole disk","Boot partition","Add a user defined partition","Go on.  Free space $0 $1.","Abort.  Not enough space, $0 $1 missing!","The start value you specified is beyond the end of the disk.\n"
"","With this value, the partition end is beyond the end of the disk.\n"
"Your partition size has been truncated.","\n"
"This disk ($0) is too large ($3) for a $2 partition table (max $4),\n"
"hence only the start of the disk is usable.\n"
"","What would you like to do to the existing partitions?","keep (use only part of disk)","delete (all data will be lost!)","convert to another partitioning method","abort","Could not convert all partitions","We now have your $2 partitions for $0 below.\n"
"This is your last chance to change them.\n"
"\n"
"Flags: $3(N)ewfs$4.   Total size: $5, free: $6","Start","End","FS type","Partition sizes ok","The current values for this partition are\n"
"displayed below.\n"
"\n"
"Select the field you wish to change:","newfs","mount","mount options","mount point","Toggle","Restore original values","Select the type","other types","Special values that can be entered for the size value:\n"
"    -1:   use until the end","   $0:   use until the given partition","Size (max $1 $2)","Special values that can be entered for the offset value:\n"
"    -1:   start at the beginning","   $0:   start at the end of given partition","   $1:   start at the beginning of given free space","Start ($2)","Badly formed number","Please enter a name for your NetBSD disk","Ok, we are now ready to install NetBSD on your hard disk (%s).  Nothing has been\n"
"written yet.  This is your last chance to quit this process before anything\n"
"gets changed.\n"
"\n"
"Shall we continue?\n"
"","Ok, the first part of the procedure is finished.  Sysinst has\n"
"written a disklabel to the target disk, and newfs'ed and fsck'ed\n"
"the new partitions you specified for the target disk.\n"
"","Ok, the first part of the procedure is finished.  Sysinst has\n"
"written a disklabel to the target disk, and fsck'ed the new\n"
"partitions you specified for the target disk.\n"
"","Could not open %s, error message was: %s.\n"
"","mount of device $0 on $1 failed.\n"
"","The extraction of the selected sets for NetBSD-10.99.10 is complete.\n"
"The system is now able to boot from the selected hard disk.  To complete\n"
"the installation, sysinst will give you the opportunity to configure\n"
"some essential things first.\n"
"","The installation of NetBSD-10.99.10 is now complete.  The system\n"
"should boot from hard disk.  Follow the instructions in the INSTALL\n"
"document about final configuration of your system.  We also recommend\n"
"reading the afterboot(8) manpage; it contains a list of things to be\n"
"checked after the first complete boot.\n"
"\n"
"At a minimum, you should edit /etc/rc.conf to match your needs.  See\n"
"/etc/defaults/rc.conf for the default values.\n"
"","The upgrade to NetBSD-10.99.10 is now complete.  You will\n"
"now need to follow the instructions in the INSTALL document as to\n"
"what you need to do to get your system reconfigured for your situation.\n"
"Remember to (re)read the afterboot(8) manpage as it may contain new\n"
"items since your last upgrade.\n"
"","Unpacking additional release sets of NetBSD-10.99.10 is now complete.  \n"
"You will now need to follow the instructions in the INSTALL document\n"
"to get your system reconfigured for your situation.\n"
"The afterboot(8) manpage can also be of some help.\n"
"\n"
"If you unpacked the etc set, you will need to edit /etc/rc.conf to get a\n"
"multi-user system.  At a minimum, you will need to change rc_configured=NO\n"
"to rc_configured=YES.\n"
"","Your disk is now ready for installing the kernel and the distribution\n"
"sets.  As noted in your INSTALL notes, you have several options.  For\n"
"ftp or nfs, you must be connected to a network with access to the proper\n"
"machines.\n"
"\n"
"Sets selected %d, processed %d, Next set %s.\n"
"\n"
"","The NetBSD distribution is broken into a collection of distribution\n"
"sets.  There are some basic sets that are needed by all installations\n"
"and there are some other sets that are optional.  You may choose to install\n"
"a core set (Minimal installation), all of them (Full installation), or a custom\n"
"group of sets (Custom installation).\n"
"","The following are the $1 site, directory, user, and password that\n"
"will be used.  If \"user\" is \"ftp\", then the password is not needed.\n"
"\n"
"","e-mail address","device","Enter the nfs host and server directory where the distribution is located. \n"
"Remember, the directory should contain the $0 files and\n"
"must be nfs mountable.\n"
"\n"
"","Enter the floppy device to be used and transfer directory on the target\n"
"file system.  The set files must be in the root directory of the floppies.\n"
"\n"
"","Enter the CDROM device to be used and directory on the CDROM where\n"
"the distribution is located. \n"
"Remember, the directory should contain the $0 files.\n"
"\n"
"","Could not locate a CD medium in any drive with the distribution sets! \n"
"Enter the correct data manually, or insert a disk and retry. \n"
"","Cancel installation","Back to source selection & retry","Available CDs ","Multiple CDs found.  Please select the one containing the install CD.","The installation sets have not been found at the default location on this\n"
"CD.  Please check the device and path name.","Enter the unmounted local device and directory on that device where\n"
"the distribution is located. \n"
"Remember, the directory should contain the $0 files.\n"
"\n"
"","Enter the already-mounted local directory where the distribution is located. \n"
"Remember, the directory should contain the $0 files.\n"
"\n"
"","file system","I can not find any network interfaces for use by NetBSD.  You will be\n"
"returned to the previous menu.\n"
"","The following network interfaces are active: %s\n"
"Does one of them connect to the required server?","Which network device would you like to use?","Available interfaces","To be able to use the network, we need answers to the following:\n"
"\n"
"","Your DNS domain","Your host name","Your IPv4 address","Server IPv4 address","IPv4 Netmask","Your name server","IPv4 gateway","Network media type","Wi-Fi SSID?","Wi-Fi passphrase?","The following are the values you entered.\n"
"\n"
"DNS Domain:		%s \n"
"Host Name:		%s \n"
"Nameserver:		%s \n"
"Primary Interface:	%s \n"
"Media type:		%s \n"
"Host IP:		%s \n"
"Netmask:		%s \n"
"IPv4 Gateway:		%s \n"
"","The following are the values you entered.  Are they OK?\n"
"\n"
"DNS Domain:		%s \n"
"Host Name:		%s \n"
"Nameserver:		%s \n"
"Primary Interface:	%s \n"
"Media type:		%s \n"
"Host IP:		%s \n"
"Server IP:		%s \n"
"Netmask:		%s \n"
"IPv4 Gateway:		%s \n"
"","IPv6 autoconf:		%s \n"
"","Are they OK?","\n"
"Waiting while network interface comes up.\n"
"","Could not create /etc/resolv.conf.  Install aborted.\n"
"","Could not change to directory $0: $1.\n"
"Install aborted.","Delete after install","Release set $0 does not exist.","All selected distribution sets unpacked successfully.","There were problems unpacking distribution sets.\n"
"Your installation is incomplete.\n"
"\n"
"You selected %d distribution sets.  %d sets couldn't be found\n"
"and %d were skipped after an error occurred.  Of the %d\n"
"that were attempted, %d unpacked without errors and %d with errors.\n"
"\n"
"Aborting installation.  Please recheck your distribution source\n"
"and consider reinstalling sets from the main menu.","Install aborted.","Partitioning aborted.","The distribution was not successfully loaded.  You will need to proceed\n"
"by hand.  Installation aborted.\n"
"","The distribution was not successfully loaded.  You will need to proceed\n"
"by hand.  Upgrade aborted.\n"
"","Unpacking additional sets was not successful.  You will need to\n"
"proceed by hand, or choose a different source for release sets and try\n"
"again.\n"
"","There is a big problem!  Can not create /mnt/etc/fstab.  Bailing out!\n"
"","Help! No /etc/fstab in target disk %s.  Aborting upgrade.\n"
"","Help! Can't parse /etc/fstab in target disk %s.  Aborting upgrade.\n"
"","I cannot save %s/bin/X as %s/bin/X.old, because the\n"
"target disk already has an %s/bin/X.old.  Please fix this before\n"
"continuing.\n"
"\n"
"One way is to start a shell from the Utilities menu, examine the\n"
"target %s/bin/X and %s/bin/X.old.  If\n"
"%s/bin/X.old is from a completed upgrade, you can rm -f\n"
"%s/bin/X.old and restart.  Or if %s/bin/X.old is from\n"
"a recent, incomplete upgrade, you can rm -f %s/bin/X and mv\n"
"%s/bin/X.old to %s/bin/X\n"
"\n"
"Aborting upgrade.","There was a problem in setting up the network.  Either your gateway\n"
"or your nameserver was not reachable by a ping.  Do you want to\n"
"configure your network again?  (\"No\" allows you to continue anyway\n"
"or abort the install process.)\n"
"","Would you like to continue the install process anyway, and assume\n"
"that the network is working?  (\"No\" aborts the install process.)\n"
"","Making device nodes ...\n"
"","It appears that $0 is not a $1 file system or the fsck was\n"
"not successful.  Try mounting it anyway?  (Error number $2.)\n"
""," target root is missing %s.\n"
"","The completed new root file system failed a basic sanity check.\n"
"Are you sure you installed all the required sets?\n"
"","Floppy file system type","Could not find the file on the floppy.\n"
"","The floppy was not mounted successfully. \n"
"","Please load the floppy containing the file named \"%s.%s\".\n"
"\n"
"If the set has no more disks, select \"Set finished\" to install the set.\n"
"Select \"Abort fetch\" to return to the install media selection menu.\n"
"","Is the network information you entered accurate for this machine\n"
"in regular operation and do you want it installed in /etc? ","The following is the list of distribution sets that will be used.\n"
"\n"
"","   Distribution set         Selected\n"
"   ------------------------ --------\n"
"","Base","Configuration files (/etc)","Compiler tools","Devicetree hardware descriptions","Games","Graphics driver firmware","Manual pages","Miscellaneous","Kernel modules","Recovery tools","Test programs","Text processing tools","X11 sets","X11 base and clients","X11 configuration","X11 fonts","X11 servers","X11 programming","Source and debug sets","Kernel sources","Base sources","Share sources","GNU sources","X11 sources","Debug symbols","X11 debug symbols","Select all the above sets","Deselect all the above sets","Install selected sets","There was an error in extracting the file %s.  That means\n"
"some files were not extracted correctly and your system will not be\n"
"complete.\n"
"\n"
"Continue extracting sets?","There must be a single partition marked to be mounted on '/'.","partitions $0 and $1 overlap.","No bootcode for specified FS type of root partition","Sorry, the root file system can't be FFSv2 due to lack of bootloader support\n"
"on this port.","\n"
"\n"
"You can either edit the partition table by hand, or give up and return\n"
"to the main menu.\n"
"\n"
"Edit the partition table again?","Could not open config file $0","Please choose the timezone that fits you best from the list below. \n"
"Press RETURN to select an entry. \n"
"Press 'x' followed by RETURN to quit the timezone selection. \n"
"\n"
" Default:	%s \n"
" Selected:	%s \n"
" Local time: 	%s %s \n"
""," Back to main timezone list","The disk that you selected has a swap partition that may currently be\n"
"in use if your system is low on memory.  Because you are going to\n"
"repartition this disk, this swap partition will be disabled now.  Please\n"
"beware that this might lead to out of swap errors.  Should you get such\n"
"an error, please restart the system and try again.","Sysinst failed to deactivate the swap partition on the disk that you\n"
"chose for installation.  Please reboot and try again.","The root password of the newly installed system has not yet been initialized,\n"
"and is thus empty.  Do you want to set a root password for the system now?","The root password of the newly installed system has not yet been\n"
"initialized. \n"
" \n"
"If you do not want to set a password, enter an empty line.","You can now select which shell to use for the root user.  The default is\n"
"/bin/sh, but you may prefer another one.","\n"
"There is no defined root file system.  You need to define at least\n"
"one mount point with \"/\".\n"
"\n"
"Press <return> to continue.\n"
"","\n"
"Enter slattach flags\n"
"","Pick an option to turn on or off.","Scripting","Logging"," Status: ","Command: ","Running","Finished","Command failed","Command ended on signal","NetBSD-10.99.10 Install System","Exit Install System","Install NetBSD to hard disk","Upgrade NetBSD on a hard disk","Re-install sets or install additional sets","Reboot the computer","Utility menu","Config menu","Back to main menu","Exit","NetBSD-10.99.10 Utilities","Run /bin/sh","Set timezone","Configure network","Partition a disk","Logging functions","Halt the system","Yes or no?","Hit enter to continue","Choose your installation","Use existing $1 partitions","Set sizes of NetBSD partitions","Use default partition sizes","Manually define partitions","Delete everything, use different partitions (not $1)","Gigabytes","Megabytes","Bytes","Cylinders","Sectors","Install from","FTP","HTTP","NFS","CD-ROM / DVD / install image media","Floppy","Unmounted fs","Local directory","Select your distribution","Full installation","Installation without X11","Minimal installation","Custom installation","** hidden **","Host","Base directory","Binary set directory","Source set directory","File extension","Transfer directory","Download via","User","Password","Proxy","Get Distribution","Continue","Continue?","What do you want to do?","Try again","Set finished","Skip set","Skip set group","Abandon installation","Abort fetch","Device","File system","  Select DNS server","other ","Perform autoconfiguration?","Root shell","User shell","Color scheme","White on black","Black on white","White on blue","Green on black","The directory where the old a.out shared libraries should be moved to could\n"
"not be created.  Please try the upgrade procedure again and make sure you\n"
"have mounted all file systems.","Either the /emul/aout or /emul directory on your system was a symbolic link\n"
"pointing to an unmounted file system.  It has been given a '.old' extension.\n"
"Once you bring your upgraded system back up, you may need to take care\n"
"of merging the newly created /emul/aout directory with the old one.\n"
"","Sendmail is no longer in this release of NetBSD, default MTA is\n"
"postfix.  The file /etc/mailer.conf still chooses the removed\n"
"sendmail.  Do you want to upgrade /etc/mailer.conf automatically for\n"
"postfix? If you choose \"No\" you will have to update /etc/mailer.conf\n"
"yourself to ensure proper email delivery.","To use the network interface %s, you must agree to the license in\n"
"file %s.  To view this file now, you can type ^Z, look at the contents of\n"
"the file and then type \"fg\" to resume.","To configure the binary package system, please choose the network location\n"
"to fetch packages from.  Once your system comes up, you can use 'pkgin'\n"
"to install additional packages, or remove packages.","Enabling binary packages with pkgin requires setting up the repository.\n"
"The following are the host, directory, user, and password that\n"
"will be used.  If \"user\" is \"ftp\", then the password is not needed.\n"
"\n"
"","Making backup of rc.conf failed.  Continue?","rc.conf backup saved to %s.","Restoring backup rc.conf failed.","Deleting old %s entry failed.","Package directory","configure a prior installation of","configure","change","password set","YES","NO","DONE","Abandoned","***EMPTY***","Timezone","Change root password","Enable installation of binary packages","Enable sshd","Enable ntpd","Run ntpdate at boot","Enable multicast DNS support","Enable xdm","Enable cgd","Enable lvm","Enable raidframe","Add a user","Configure the additional items as needed.","Finished configuring","Install pkgin and update package summary","Your system is now configured to use pkgin to install binary packages.  To\n"
"install a package, run:\n"
"\n"
"pkgin install <packagename>\n"
"\n"
"from a root shell.  Read the pkgin(1) manual page for further information.","Fetch and unpack pkgsrc","Installing pkgsrc requires unpacking an archive retrieved over the network.\n"
"The following are the host, directory, user, and password that\n"
"will be used.  If \"user\" is \"ftp\", then the password is not needed.\n"
"\n"
"","pkgsrc directory","Fetch and unpack pkgsrc","Network configuration failed.  Retry?","Quit without installing pkgsrc","Quit installing binary pkgs","Installation of pkgin failed, possibly because no binary packages\n"
"exist.  Please check the package path and try again.","Failed","Mountpoint (or 'raid', 'cgd', 'lvm')?","Extended partitioning","Edit partitions","Preconfigured \"wedges\" dk(4)","REMOVE","Remove","Add","auto","This removes all partitions on the disk!","Save changes before finishing?","Changes cannot be saved.","No root partition defined.  Cannot continue\n","8 character username to add","Do you wish to add this user to group wheel?","Delete partition","The selected partition does not seem to have a valid file system. \n"
"Do you want to newfs (format) it?","swap","A swap partition (named $1) \n"
"seems to exist on $0. \n"
"Do you want to use that?","BSD disklabel","disklabel","disklabel (NetBSD only)","The disk seems not to have been partitioned before. Please select\n"
"a partitioning scheme from the available options below. ","Please select a different partitioning scheme from the available\n"
"options below. ","Some schemes have size limits and can only be used for the start\n"
"of huge disks. The limit is displayed below.","This device ($0) is $1 big.","Max:","Add a partition","      (no partition defined)","Unknown","Invalid file system type code (0 .. 255)","Cancel","Invalid value","Invalid GUID","Re-edit","Abort installation","File system type code (upto 255)","Too many partitions","$0 already defined!","This is an already existing partition. \n"
"To change its size, the partition will need to be deleted and later\n"
"recreated.  All data in this partition will be lost.\n"
"\n"
"Would you like to delete this partition and continue?","Non-deletable system partition","type","start","size","end","block size","fragment size","avg file size","$0 bytes (for number of inodes)","4 fragments","Select file system block size","Select file system fragment size","average file size (bytes)","No free space","Invalid numeric!","Too large!","Space at $0..$1 $3 (size $2 $3)\n","FFSv2","FFSv2ea","FFS","EFI system partition","Linux Ext2 (old)","Other type","Edit name of the disk","The name of the disk is arbitrary. \n"
"It is useful for distinguishing between multiple disks.\n"
"It may also be used when auto-creating dk(4) \"wedges\" for this disk. \n"
"\n"
"Enter disk name","Do you want to re-edit the $1 partitions?","We are now going to install NetBSD on the disk $0.\n"
"\n"
"NetBSD requires a single partition in the disk's $1\n"
"partition table, this is split further by the $2.\n"
"NetBSD can also access file systems in other $3 partitions.\n"
"\n"
"If you select 'Use the entire disk' then the previous contents of the\n"
"disk will be overwritten and a single $3 partition used to cover the\n"
"entire disk. \n"
"If you want to install more than one operating system then edit the\n"
"$3 partition table and create a partition for NetBSD.\n"
"\n"
"About $5 is enough for a basic installation, but you should allow\n"
"extra for additional software and user files. \n"
"Allow at least $6 if you want to build NetBSD itself.","What would you like to do?","Edit the $1 partition table","Use the entire disk","   Total size of $0 is $1, available: $2","Start","Size","Flag","Partition table OK","Don't change","Other","There is no NetBSD partition in the $1.","There are multiple NetBSD partitions in the $1.\n"
"You should set the 'install' flag on the one you want to use.","Your disk currently has a non-NetBSD partition.  Do you really want to\n"
"overwrite that partition with NetBSD?\n"
"","Partition OK","The Current $2 partition table of $0 is shown below. \n"
"Flags: (I)nstall here$3. \n"
"Select the partition you wish to change:\n"
"\n"
"","I","N","C",", (C)lone","install","(I)nstall, ","Guid Partition Table (GPT)","GPT","Label","UUID","GPT Type","Boot","Use this partitions anyway","B",", (B)ootable","(Other: $0)","current system","Clone external partition(s)","Please select an external source partition:","Your currently selected source partitions are:","Clone with data","Add another partition","Add at end","Insert cloned partitions before:","cloned partition(s)","Source selection OK, proceed to target selection","Your network seems to work fine. \n"
"Should we skip the configuration \n"
"and just use the network as-is?","\n"
"","\n"
"","Keyboard type","","Installing the bad block table ...\n"
"","Would you like to install the normal set of bootblocks or serial bootblocks?\n"
"\n"
"Normal bootblocks use the BIOS console device as the console\n"
"(usually the monitor and keyboard). Serial bootblocks use the first\n"
"serial port as the console.\n"
"\n"
"Selected bootblock: ","BIOS console","Serial port com%d at %d baud","Unchanged","Bootblocks selection","Use BIOS console","Use serial port com0","Use serial port com1","Use serial port com2","Use serial port com3","Set serial baud rate","Use existing bootblocks","Installing boot blocks on %s....\n"
"","This disk matches the following BIOS disk:\n"
"\n"
"","BIOS # cylinders heads sectors total sectors   GB \n"
"------ --------- ----- ------- ------------- ---- \n"
"","%#6x %9d %5d %7d %13u %3u\n","This is the correct geometry","Set the geometry by hand","Use one of these disks","This disk matches the following BIOS disks:\n"
"\n"
"","   BIOS # cylinders heads sectors total sectors   GB \n"
"   ------ --------- ----- ------- ------------- ---- \n"
"","%-1d: %#6x %9d %5d %7d %13u %3u\n","\n"
"Note: since sysinst was able to uniquely match the disk you chose with a disk\n"
"known to the BIOS, the values displayed above are very likely correct, and\n"
"should not be changed (the values for cylinders, heads and sectors are\n"
"probably 1023, 255 and 63 - this is correct). \n"
"You should only change the geometry if you know the BIOS reports incorrect\n"
"values.\n"
"","Choose disk: ","The NetBSD part of the disk lies outside of the range that the BIOS on\n"
"your machine can address.\n"
"Booting from it may not be possible. \n"
"Are you sure you that you want to do this?\n"
"\n"
"(Answering 'no' will take you back to the partition edit menu.)","You have more than one operating system on this disk, but have not\n"
"specified a 'bootmenu' for either the active partition, or the\n"
"NetBSD partition that you are going to install into.\n"
"\n"
"Do you want to re-edit the partition to add a bootmenu entry?","You have requested that an extended partition be included in the bootmenu.\n"
"However your system BIOS doesn't appear to support the read command used\n"
"by that version of the bootmenu code. \n"
"Are you sure you that you want to do this?\n"
"\n"
"(Answering 'no' will take you back to the partition edit menu.)","Your configuration requires the NetBSD bootselect code to\n"
"select which operating system to use.\n"
"\n"
"It is not currently installed, do you want to install it now?","The bootcode in the Master Boot Record does not appear to be valid.\n"
"\n"
"Do you want to install the NetBSD bootcode?","Do you want to update the bootcode in the Master Boot Record to\n"
"the latest version of the NetBSD bootcode?","Kernel (GENERIC)","Kernel (GENERIC_KASLR)","Kind","Mount","Bootmenu","You have not marked a partition active. This may cause your system to not\n"
"start up properly.","\n"
"Should the NetBSD partition of the disk be marked active?","\n"
"You will be prompted for the geometry.\n"
"Please enter the number of sectors per track (maximum 63)\n"
"and number of heads (maximum 256) that the BIOS uses to access the disk. \n"
"The number of cylinders will be calculated from the disk size.\n"
"\n"
"","Sysinst could not automatically determine the BIOS geometry of the disk. \n"
"The physical geometry is %d cylinders %d sectors %d heads\n","Using the information already on the disk, my best guess for the BIOS\n"
"geometry is %d cylinders %d sectors %d heads\n","real geom: %d cyl, %d heads, %d sec  (NB: for comparison only)\n","BIOS geom: %d cyl, %d heads, %d sec\n","active","bootmenu","default","Partition kind (0..255)","There can only be one extended partition","ad",", (a)ctive, (d)efault boot","Writing the $2 partition table to $0...\n"
"","Rewrite of MBR failed. I can't continue.","The partition needs to start within the Extended Partition","The Extended Partition must be able to hold all contained partitions","Can not delete a non-empty extended partition!","This partition is not inside the extended partition\n"
"and there is no free slot in the primary boot record","No space in the primary boot block.\n"
"You may consider deleting one partition, creating an extended partition\n"
"and then re-adding the deleted one","Master Boot Record (MBR)","MBR","Invalid partition type (0 .. 255)","Fill with zeros","Fill with random data","0 - No parity, simple striping.","1 - Mirroring.  The parity is the mirror.","4 - Striping with parity stored on the last component.","5 - Striping with distributed parity.","\n"
"Device is blocked.  Editing it may cause problems.\n"
"Do you want to force unblock it and continue?","Do you want to try?","Create cryptographic volume (CGD)","Create virtual disk image (VND)","Create volume group (LVM VG)","Create logical volume","Create software RAID","Update device list","Save changes","BLOCKED","UNCHANGED","USED","(mounted)","(unused)","GPT-labeled disk","Finish partitioning","Limit for the device count was reached!","Invalid device!","Available disks:","Cannot allocate device node!","This is the extended partition manager.  All disks, partitions, etc. are\n"
"listed below.  To use RAID, LVM, or CGD: 1) Create partitions with the\n"
"appropriate type; 2) Create RAID/LVM VG/CGD using these partitions; 3) Save\n"
"changes; 4) Create partitions for RAID/CGD or Logical Volumes for LVM.","on","$0 (level $1)","EMPTY RAID!","Disks","Spares","RAID level","numRow","numCol","numSpare","sectPerSU","SUsPerParityUnit","SUsPerReconUnit","Multi-dimensional arrays are NOT supported!","numRow?","numCol?","numSpare?","sectPerSU?","SUsPerParityUnit?","SUsPerReconUnit?","Disks in RAID:","PATH NOT DEFINED!","ASSIGN","File path","Create new image","Size","Read-only","Set geometry by hand","Bytes per Sector","Sectors per Track","Tracks per Cylinder","Cylinders","File path?","Size (MB)?","Bytes per Sector?","Sectors per Track?","Tracks per Cylinder?","Cylinders?","DISK NOT DEFINED!","Base device","Encryption","Key size","IV algorithm","Key generation","Verification method","Disks in VG","EMPTY VG!","PV's","Name","MaxLogicalVolumes","MaxPhysicalVolumes","PhysicalExtentSize","Name?","MaxLogicalVolumes?","MaxPhysicalVolumes?","PhysicalExtentSize?","Logical volume","Name","Size","Read-only","Contiguous","LogicalExtentsNumber","Minor number","Mirrors","MirrorLogRegionSize","Persistent minor number","ReadAheadSectors","Stripes","StripeSize","Zeroing of the first KB","Name?","Size (MB)?","LogicalExtentsNumber?","Minor number?","Mirrors?","MirrorLogRegionSize?","ReadAheadSectors?","Stripes?","Operation not supported!","Edit partitions","Switch partitioning scheme","Format as RAID","Format as LVM PV","Encrypt (CGD)","Safe erase","Undo changes","Unconfigure","Edit","Force umount","Set up entropy","Not now, continue!","This system seems to lack a cryptographically strong pseudo random\n"
"number generator. There is not enough entropy available to create secure\n"
"keys (e.g. ssh host keys). \n"
" \n"
"If you plan to use this installation for production work and will\n"
"for example have ssh host keys generated, we strongly advise to complete\n"
"the entropy setup now! \n"
" \n"
"You may use random data generated on another computer and load it\n"
"here, or you could enter random characters manually. \n"
" \n"
"If you have a USB random number device, connect it now and select\n"
"the \"Re-test\" option.","Manually input random characters","Load raw binary random data","Import a NetBSD entropy file","Re-test","Enter one line of random characters.","They should contain at last 256 bits of randomness, as in 256 coin\n"
"tosses, 100 throws of a 6-sided die, 64 random hexadecimal digits, or\n"
"(if you are able to copy & paste output from another machine into this\n"
"installer) the output from running the following command on another\n"
"machine whose randomness you trust:","A line of any length and content will be accepted and assumed to\n"
"contain at least 256 bits of randomness.  If it actually contains\n"
"less, the installed system may not be secure.","Please select how you want to transfer the random data file\n"
"to this machine:","Download via ftp","Download via http","Start download","Load from a NFS share","Load from a local file system (e.g. a USB device)","Path/file","Load random data","Random data file path","Select a server, a share and the file path to load the $0.","Since not enough entropy is available on this system, all crytographic\n"
"operations are suspect to replay attacks. \n"
"Please only use trustworthy local networks.","random data binary file","On a system with cryptographically strong pseudo random number generator\n"
"you can create a file with random binary data like this:","NetBSD entropy seed file","On a NetBSD system with cryptographically strong pseudo random number\n"
"generator you can create an entropy snapshot like this:","Path and filename","Enter the unmounted local device and directory on that device where\n"
"the random data is located.",NULL};
/*	$NetBSD: msg_sys.def,v 1.48 2019/11/16 17:38:09 martin Exp $	*/

/*
 * Copyright 1997 Piermont Information Systems Inc.
 * All rights reserved.
 *
 * Written by Philip A. Nelson for Piermont Information Systems Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of Piermont Information Systems Inc. may not be used to endorse
 *    or promote products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY PIERMONT INFORMATION SYSTEMS INC. ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL PIERMONT INFORMATION SYSTEMS INC. BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

static WINDOW *msg_win = NULL;
static char *cbuffer;
static size_t cbuffersize;

static int last_i_was_nl, last_i_was_space;
static int last_o_was_punct, last_o_was_space;

static void	_msg_beep(void);
static int	_msg_vprintf(int, const char *, va_list);
#define MSG_PROMPT_ECHO		1
#define MSG_PROMPT_HIDE_DFLT	2
static void	_msg_vprompt(const char *, int, const char *, char *,
			size_t, va_list);

static char *msgmap = MAP_FAILED;
static size_t msgmapsz;
static unsigned int msgmapcount;

/* Routines */

static void
_msg_beep(void)
{

	fprintf(stderr, "\a");
}

WINDOW *
msg_window(WINDOW *window)
{
	size_t ncbuffersize;
	char *ncbuffer;
	WINDOW *old;

	old = msg_win;
	if (!window)
		return old;
	msg_win = window;

	ncbuffersize = getmaxx(window) * getmaxy(window) + 1;
	while (ncbuffersize > cbuffersize) {
		ncbuffer = malloc(ncbuffersize);
		if (ncbuffer == NULL) {
			/* we might get truncated messages... */
			ncbuffersize <<= 1;
			continue;
		}
		if (cbuffer != NULL)
			free(cbuffer);
		cbuffer = ncbuffer;
		cbuffersize = ncbuffersize;
		break;
	}
	last_o_was_punct = 0;
	last_o_was_space = 1;
	return old;
}

int
msg_file(const char *file)
{
	int fd;

	if (msgmap != MAP_FAILED)
		munmap(msgmap, msgmapsz);
	msgmap = MAP_FAILED;
	if (!file)
		return 0;
	fd = open(file, O_RDONLY, 0);
	if (fd == -1)
		return -1;
	msgmapsz = lseek(fd, 0, SEEK_END);
	msgmap = mmap(0, msgmapsz, PROT_READ, MAP_SHARED, fd, 0);
	close(fd);
	if (msgmap == MAP_FAILED)
		return -1;
	/* check_magic */
	if (strcmp(msgmap, "MSGTXTS") != 0) {
		msg_file(NULL);
		return -1;
	}
	msgmapcount = atoi(msgmap + 8);
	return 0;
}

const char *
msg_string(msg msg_no)
{
	uintptr_t m = (uintptr_t)msg_no;

	if (m > sizeof msg_list / sizeof msg_list[0])
		/* guess that we were passed a text string */
		return msg_no;

	if (msgmap != MAP_FAILED && m != 0 && m <= msgmapcount) {
		unsigned int offset = atoi(msgmap + 8 + 8 * m);
		if (offset != 0 && offset < msgmapsz)
			return msgmap + offset;
	}

	return msg_list[m];
}

void
msg_clear(void)
{

	wclear(msg_win);
	last_o_was_punct = 0;
	last_o_was_space = 1;
}

void
msg_standout(void)
{

	wstandout(msg_win);
}

void
msg_standend(void)
{

	wstandend(msg_win);
}

static int __printflike(2, 0)
_msg_vprintf(int auto_fill, const char *fmt, va_list ap)
{
	const char *wstart, *afterw;
	int wordlen, nspaces;
	int ret;

	ret = vsnprintf(cbuffer, cbuffersize, fmt, ap);

	if (!auto_fill) {
		waddstr(msg_win, cbuffer);

		/*
		 * nothing is perfect if they flow text after a table,
		 * but this may be decent.
		 */
		last_i_was_nl = last_i_was_space = 1;
		last_o_was_punct = 0;
		last_o_was_space = 1;
		goto out;
	}

	for (wstart = afterw = cbuffer; *wstart; wstart = afterw) {

		/* eat one space, or a whole word of non-spaces */
		if (isspace((unsigned char)*afterw))
			afterw++;
		else
			while (*afterw && !isspace((unsigned char)*afterw))
				afterw++;

		/* this is an nl: special formatting necessary */
		if (*wstart == '\n') {
			if (last_i_was_nl || last_i_was_space) {

				if (getcurx(msg_win) != 0)
					waddch(msg_win, '\n');
				if (last_i_was_nl) {
					/* last was an nl: paragraph break */
					waddch(msg_win, '\n');
				} else {
					/* last was space: line break */
				}
				last_o_was_punct = 0;
				last_o_was_space = 1;
			} else {
				/* last_o_was_punct unchanged */
				/* last_o_was_space unchanged */
			}
			last_i_was_space = 1;
			last_i_was_nl = 1;
			continue;
		}

		/* this is a tab: special formatting necessary. */
		if (*wstart == '\t') {
			if (last_i_was_nl) {
				/* last was an nl: list indent */
				if (getcurx(msg_win) != 0)
					waddch(msg_win, '\n');
			} else {
				/* last was not an nl: columns */
			}
			waddch(msg_win, '\t');
			last_i_was_nl = 0;
			last_i_was_space = 1;
			last_o_was_punct = 0;
			last_o_was_space = 1;
			continue;
		}

		/* this is a space: ignore it but set flags */
		last_i_was_nl = 0;	/* all newlines handled above */
		last_i_was_space = isspace((unsigned char)*wstart);
		if (last_i_was_space)
			continue;

		/*
		 * we have a real "word," i.e. a sequence of non-space
		 * characters.  wstart is now the start of the word,
		 * afterw is the next character after the end.
		 */
		wordlen = afterw - wstart;
		nspaces = last_o_was_space ? 0 : (last_o_was_punct ? 2 : 1);
		if ((getcurx(msg_win) + nspaces + wordlen) >=
		      getmaxx(msg_win) &&
		    wordlen < (getmaxx(msg_win) / 3)) {
			/* wrap the line */
			waddch(msg_win, '\n');
			nspaces = 0;
		}

		/* output the word, preceded by spaces if necessary */
		while (nspaces-- > 0)
			waddch(msg_win, ' ');
		waddbytes(msg_win, wstart, wordlen);

		/* set up the 'last' state for the next time around */
		switch (afterw[-1]) {
		case '.':
		case '?':
		case '!':
			last_o_was_punct = 1;
			break;
		default:
			last_o_was_punct = 0;
			break;
		}
		last_o_was_space = 0;

		/* ... and do it all again! */
	}

	/* String ended with a newline.  They really want a line break. */
	if (last_i_was_nl) {
		if (getcurx(msg_win) != 0)
			waddch(msg_win, '\n');
		last_o_was_punct = 0;
		last_o_was_space = 1;
	}

out:
	wrefresh(msg_win);
	return ret;
}

void
msg_display(msg msg_no)
{

	msg_clear();
	msg_printf("%s", msg_string(msg_no));
}

void __printflike(2, 3)
msg_fmt_display(msg msg_no, const char *fmt, ...)
{
	va_list ap;

	msg_clear();

	va_start(ap, fmt);
	(void)_msg_vprintf(1, fmtcheck(msg_string(msg_no), fmt), ap);
	va_end(ap);
}

void
msg_display_add(msg msg_no)
{

	msg_printf("%s", msg_string(msg_no));
}

void __printflike(2, 3)
msg_fmt_display_add(msg msg_no, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	(void)_msg_vprintf(1, fmtcheck(msg_string(msg_no), fmt), ap);
	va_end(ap);
}

void __printflike(1, 2)
msg_printf(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	(void)_msg_vprintf(1, fmt, ap);
	va_end(ap);
}

static void __printflike(1, 0)
_msg_vprompt(const char *fmt, int flags, const char *def, char *val,
    size_t val_buf_len, va_list ap)
{
	int ch;
	int len, pos, npos, off;
	int first;
	int txt_y, txt_x;
	char *ibuf;
	int maxx;

	if (val == NULL || val_buf_len == 0) {
		/* No answer wanted */
		val = NULL;
		val_buf_len = 1;
	}

	ibuf = malloc(val_buf_len);

	keypad(msg_win, TRUE);
	_msg_vprintf(0, fmt, ap);
	ibuf[0] = 0;
	if (def != NULL && *def) {
		if (flags & MSG_PROMPT_HIDE_DFLT)
			strlcpy(ibuf, def, val_buf_len);
		else {
			waddstr(msg_win, " [");
			waddstr(msg_win, def);
			waddstr(msg_win, "]");
		}
	}
	waddstr(msg_win, ": ");
	len = strlen(ibuf);
	pos = len;
	getyx(msg_win, txt_y, txt_x);
	maxx = getmaxx(msg_win) - txt_x - 1;
	off = 0;

	for (first = 1; ; first = 0) {

		if (flags & MSG_PROMPT_ECHO) {
			/* shift text right as we near the buffer start */
			if (pos - off < 4)
				off = pos - 4;
			/* keep offset to a minimum if we are at the end */
			if (pos == len)
				off = pos - maxx;
			if (off < 0 || len <= maxx)
				off = 0;
			/* shift text left as we near the buffer end */
			npos = pos + 4;
			if (npos > len)
				npos = len;
			if (npos - off > maxx)
				off = npos - maxx;
			/* calc. length to display */
			npos = len - off;
			if (npos > maxx)
				npos = maxx;
			mvwaddnstr(msg_win, txt_y, txt_x, ibuf + off, npos);
			wclrtoeol(msg_win);
			if (off != 0)
				mvwaddstr(msg_win, txt_y, txt_x, "+");
			wmove(msg_win, txt_y, txt_x + pos - off);
			wrefresh(msg_win);
		}

		ch = wgetch(msg_win);
		if (ch == '\n')
			break;

		switch (ch) {
		case KEY_BACKSPACE:
		case 'h' & 0x1f: case 0x7f:  /* bs or del - delete left */
			if (first) {
				/* delete all of default string */
				len = pos = 0;
				break;
			}
			if (pos > 0) {
				memmove(ibuf + pos - 1, ibuf + pos, len - pos);
				len--;
				pos--;
			} else
				_msg_beep();
			break;
		case 'l' & 0x1f:
			endwin();
			doupdate();
			break;
		case 'u' & 0x1f:	/* ^U; line kill */
			/* kill line */
			len = pos = 0;
			break;
		case 'w' & 0x1f:        /* ^W; word kill */
			/*
			 * word kill kills the spaces and the 'word'
			 * (non-spaces) last typed.  the spaces before
			 * the 'word' aren't killed.
			 */
			npos = pos;
			while (npos > 0 && isspace((unsigned char)ibuf[npos - 1]))
				npos--;
			while (npos > 0 && !isspace((unsigned char)ibuf[npos - 1]))
				npos--;
			memmove(ibuf + npos, ibuf + pos, len - pos);
			len -= pos - npos;
			pos = npos;
			break;
		case KEY_LEFT:
			if (pos > 0)
				pos--;
			break;
		case KEY_RIGHT:
			if (len == 0 && pos == 0 && def != NULL) {
				/* restore default! */
				strlcpy(ibuf, def, val_buf_len);
				len = pos = strlen(ibuf);
				break;
			}
			if (pos < len)
				pos++;
			break;
		default:
			if (len < (int)(val_buf_len - 1) && isprint(ch)) {
				memmove(ibuf + pos + 1, ibuf + pos, len - pos);
				ibuf[pos++] = ch;
				len++;
			} else
				_msg_beep();
			break;
		}
	}

	if (flags & MSG_PROMPT_ECHO) {
		mvwaddch(msg_win, txt_y, txt_x + len - off, '\n');
		last_o_was_punct = 0;
		last_o_was_space = 1;
	}

	if (val != NULL) {
		/* copy the appropriate string to the output */
		if (len != 0 || flags & MSG_PROMPT_HIDE_DFLT) {
			ibuf[len] = '\0';
			strlcpy(val, ibuf, val_buf_len);
		} else if (def != NULL && val != def) {
			strlcpy(val, def, val_buf_len);
		}
	}
	free(ibuf);
}

void
msg_prompt(msg msg_no, const char *def, char *val, size_t val_buf_len)
{

	msg_fmt_prompt(msg_no, def, val, val_buf_len, "");
}

void __printflike(5, 6)
msg_fmt_prompt(msg msg_no, const char *def, char *val, size_t val_buf_len,
    const char *fmt, ...)
{
	va_list ap;

	msg_clear();

	va_start(ap, fmt);
	_msg_vprompt(fmtcheck(msg_string(msg_no), fmt), MSG_PROMPT_ECHO,
		def, val, val_buf_len, ap);
	va_end(ap);
}

void
msg_prompt_win(msg msg_no, int x, int y, int w, int h,
    const char *def, char *val, size_t val_buf_len)
{
    msg_fmt_prompt_win(msg_no, x, y, w, h, def, val, val_buf_len, "");
}

void __printflike(9, 10)
msg_fmt_prompt_win(msg msg_no, int x, int y, int w, int h,
    const char *def, char *val, size_t val_buf_len, const char *fmt, ...)
{
	va_list ap;
	WINDOW *win;
	WINDOW *svmsg = NULL, *sv_win = NULL; /* XXX -Wuninitialized [many] */
	int maxx, maxy;
	int msg_flags = MSG_PROMPT_ECHO | MSG_PROMPT_HIDE_DFLT;
	const char *np, *ep;

	maxx = getmaxx(msg_win);
	maxy = getmaxy(msg_win);
	if (w == 0) {
		va_start(ap, fmt);
		w = vsnprintf(NULL, 0, fmtcheck(msg_string(msg_no), fmt), ap);
		va_end(ap);
		if (def != NULL && *def != 0 && w + (int)val_buf_len * 2 < maxx) 		{
			w += 2 + strlen(def) + 1;
			msg_flags &= ~MSG_PROMPT_HIDE_DFLT;
		}
		w += 1 + 2 + val_buf_len + 1;
		if (w > maxx) {
			if (!(msg_flags & MSG_PROMPT_HIDE_DFLT)) {
				w -= 2 + strlen(def) + 1;
				msg_flags |= MSG_PROMPT_HIDE_DFLT;
			}
			w = maxx;
		}
	} else if (w > 0 && def != NULL && *def != 0) {
		size_t tl = strlen(def);
		if (tl + 1 + 2 + val_buf_len + 1 < (unsigned)w)
			msg_flags &= ~MSG_PROMPT_HIDE_DFLT;
	}

	if (x == -1)
		x = (maxx - w) / 2 + 1;
	if (h < 0) {
		h = 3;
		for (np = msg_string(msg_no); (ep = strchr(np, '\n'));
		    np = ep + 1)
			h++;
	}
	if (h < 3)
		h = 3;
	if (y < 3)
		y = (maxy - h) / 2;
	if (y + h > maxy)
		y = maxy - h;

	win = subwin(msg_win, h, w, y, x);
	if (win == NULL)
		wprintw(msg_win, "msg_prompt_win: "
			"newwin(%d, %d, %d, %d) failed\n",
			h, w, y, x);
	else {
		/*
		 * Save screen contents from under our window
		 * Due to a mis-feature of NetBSD curses, curscr contains
		 * the data processed by doupdate() not that by wnoutrefresh().
		 * We must call doupdate() here to ensure we save the correct
		 * data.  See PR 26660
		 */
		doupdate();
		sv_win = dupwin(win);
		if (sv_win)
			overwrite(curscr, sv_win);
		wbkgd(win, getbkgd(msg_win));
		wattrset(win, getattrs(msg_win));
		box(win, 0, 0);
		wrefresh(win);

		/* Change message window to be our little box */
		svmsg = msg_window(subwin(msg_win, h - 2, w - 2, y + 1, x + 1));
		wbkgd(msg_win, getbkgd(win));
		wattrset(msg_win, getattrs(win));

		msg_clear();
	}

	va_start(ap, fmt);
	_msg_vprompt(fmtcheck(msg_string(msg_no), fmt), msg_flags, def, val,
	    val_buf_len, ap);
	va_end(ap);

	if (win != NULL) {
		wclear(win);
		if (sv_win) {
			/* Restore original screen contents */
			overwrite(sv_win, win);
			delwin(sv_win);
		}
		wnoutrefresh(win);
		/* Restore normal message window */
		delwin(msg_window(svmsg));
		delwin(win);
	}
}

void 
msg_prompt_add(msg msg_no, const char *def, char *val, size_t val_buf_len)
{

	msg_fmt_prompt_add(msg_no, def, val, val_buf_len, "");
}

void __printflike(5, 6)
msg_fmt_prompt_add(msg msg_no, const char *def, char *val, size_t val_buf_len,
    const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	_msg_vprompt(fmtcheck(msg_string(msg_no), fmt), MSG_PROMPT_ECHO, def,
	    val, val_buf_len, ap);
	va_end(ap);
}

void
msg_prompt_noecho(msg msg_no, const char *def, char *val, size_t val_buf_len)
{
	msg_fmt_prompt_noecho(msg_no, def, val, val_buf_len, "");
}

void __printflike(5, 6)
msg_fmt_prompt_noecho(msg msg_no, const char *def, char *val,
    size_t val_buf_len, const char *fmt, ...)
{
	va_list ap;

	msg_clear();

	va_start(ap, fmt);
	_msg_vprompt(fmtcheck(msg_string(msg_no), fmt), 0, def, val,
	    val_buf_len, ap);
	va_end(ap);
}

void
msg_table_add(msg msg_no)
{

	msg_fmt_table_add(msg_no, "");
}

void __printflike(2, 3)
msg_fmt_table_add(msg msg_no, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	(void)_msg_vprintf(0, fmtcheck(msg_string(msg_no), fmt), ap);
	va_end(ap);
}

int
msg_row(void)
{

	return getcury(msg_win) + getbegy(msg_win);
}
