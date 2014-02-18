

#include "stdafx.h"
#include "TraceErrorSys.h"


void odssys(CCString Function, CCString Header, HRESULT hr)
{
    CCString Buf;
    CCString Buf2;

    TraceErrorSys(&Buf, hr);
    Buf2.FormatW(L"%s: %s", (PCWSTR)Header, (PCWSTR)Buf);

    odsf(Function, Buf2);
}


#ifdef _DEBUG
#   define ERR(a, b) \
        case a: \
        Buf->FormatA("%d (0x%08x): %s", a, a, b); \
        break;
#else
#   define ERR(a, b) \
        { \
        }
#endif
    //FormatMessage(flags, source, message id, langid, buffer, size, args)


//////////////////////////////////////////////////////////////////////////
void TraceErrorSys(CCString* Buf, HRESULT hr)
{
#ifdef NDEBUG

    PTSTR* lpMsgBuf = 0;

    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                  (PTSTR) &lpMsgBuf, 0, NULL);

    Buf->FormatW(L"%d (0x%08x): %s", hr, hr, lpMsgBuf);

    LocalFree(lpMsgBuf);

    return;

#else
    switch(hr)
    {
        ERR(1L , "ERROR_INVALID_FUNCTION: Incorrect function.")// ERROR_INVALID_FUNCTION
        ERR(2L, "ERROR_FILE_NOT_FOUND: The system cannot find the file specified.")// ERROR_FILE_NOT_FOUND
        ERR(3L, "ERROR_PATH_NOT_FOUND: The system cannot find the path specified.")// ERROR_PATH_NOT_FOUND
        ERR(4L, "ERROR_TOO_MANY_OPEN_FILES: The system cannot open the file.")// ERROR_TOO_MANY_OPEN_FILES
        ERR(5L, "ERROR_ACCESS_DENIED: Access is denied.")// ERROR_ACCESS_DENIED
        ERR(6L, "ERROR_INVALID_HANDLE: The handle is invalid.")// ERROR_INVALID_HANDLE
        ERR(7L, "ERROR_ARENA_TRASHED: The storage control blocks were destroyed.")// ERROR_ARENA_TRASHED
        ERR(8L , "ERROR_NOT_ENOUGH_MEMORY: Not enough storage is available to process this command.")// ERROR_NOT_ENOUGH_MEMORY
        ERR(9L, "ERROR_INVALID_BLOCK: The storage control block address is invalid.")// ERROR_INVALID_BLOCK
        ERR(10L, "ERROR_BAD_ENVIRONMENT: The environment is incorrect.")// ERROR_BAD_ENVIRONMENT
        ERR(11L, "ERROR_BAD_FORMAT: An attempt was made to load a program with an incorrect format.")// ERROR_BAD_FORMAT
        ERR(12L, "ERROR_INVALID_ACCESS: The access code is invalid.")// ERROR_INVALID_ACCESS
        ERR(13L, "ERROR_INVALID_DATA: The data is invalid.")// ERROR_INVALID_DATA
        ERR(14L, "ERROR_OUTOFMEMORY: Not enough storage is available to complete this operation.")// ERROR_OUTOFMEMORY
        ERR(15L, "ERROR_INVALID_DRIVE: The system cannot find the drive specified.")// ERROR_INVALID_DRIVE
        ERR(16L, "ERROR_CURRENT_DIRECTORY: The directory cannot be removed.")// ERROR_CURRENT_DIRECTORY
        ERR(17L, "ERROR_NOT_SAME_DEVICE: The system cannot move the file to a different disk drive.")// ERROR_NOT_SAME_DEVICE
        ERR(18L, "ERROR_NO_MORE_FILES: There are no more files.")// ERROR_NO_MORE_FILES
        ERR(19L, "ERROR_WRITE_PROTECT: The media is write protected.")// ERROR_WRITE_PROTECT
        ERR(20L, "ERROR_BAD_UNIT: The system cannot find the device specified.")// ERROR_BAD_UNIT
        ERR(21L, "ERROR_NOT_READY: The device is not ready.")// ERROR_NOT_READY
        ERR(22L, "ERROR_BAD_COMMAND: The device does not recognize the command.")// ERROR_BAD_COMMAND
        ERR(23L, "ERROR_CRC: Data error (cyclic redundancy check).")// ERROR_CRC
        ERR(24L, "ERROR_BAD_LENGTH: The program issued a command but the command length is incorrect.")// ERROR_BAD_LENGTH
        ERR(25L, "ERROR_SEEK: The drive cannot locate a specific area or track on the disk.")// ERROR_SEEK
        ERR(26L, "ERROR_NOT_DOS_DISK: The specified disk or diskette cannot be accessed.")// ERROR_NOT_DOS_DISK
        ERR(27L, "ERROR_SECTOR_NOT_FOUND: The drive cannot find the sector requested.")// ERROR_SECTOR_NOT_FOUND
        ERR(28L, "ERROR_OUT_OF_PAPER: The printer is out of paper.")// ERROR_OUT_OF_PAPER
        ERR(29L, "ERROR_WRITE_FAULT: The system cannot write to the specified device.")// ERROR_WRITE_FAULT
        ERR(30L, "ERROR_READ_FAULT: The system cannot read from the specified device.")// ERROR_READ_FAULT
        ERR(31L, "ERROR_GEN_FAILURE: A device attached to the system is not functioning.")// ERROR_GEN_FAILURE
        ERR(32L, "ERROR_SHARING_VIOLATION: The process cannot access the file because it is being used by another process.")// ERROR_SHARING_VIOLATION
        ERR(33L, "ERROR_LOCK_VIOLATION: The process cannot access the file because another process has locked a portion of the file.")// ERROR_LOCK_VIOLATION
        ERR(34L, "ERROR_WRONG_DISK: The wrong diskette is in the drive.")// ERROR_WRONG_DISK
        ERR(36L, "ERROR_SHARING_BUFFER_EXCEEDED: Too many files opened for sharing.")// ERROR_SHARING_BUFFER_EXCEEDED
        ERR(38L, "ERROR_HANDLE_EOF: Reached the end of the file.")// ERROR_HANDLE_EOF
        ERR(39L, "ERROR_HANDLE_DISK_FULL: The disk is full.")// ERROR_HANDLE_DISK_FULL
        ERR(50L, "ERROR_NOT_SUPPORTED: The network request is not supported.")// ERROR_NOT_SUPPORTED
        ERR(51L, "ERROR_REM_NOT_LIST: The remote computer is not available.")// ERROR_REM_NOT_LIST
        ERR(52L, "ERROR_DUP_NAME: A duplicate name exists on the network.")// ERROR_DUP_NAME
        ERR(53L, "ERROR_BAD_NETPATH: The network path was not found.")// ERROR_BAD_NETPATH
        ERR(54L, "ERROR_NETWORK_BUSY: The network is busy.")// ERROR_NETWORK_BUSY
        ERR(55L , "ERROR_DEV_NOT_EXIST: The specified network resource or device is no longer available.")// ERROR_DEV_NOT_EXIST
        ERR(56L, "ERROR_TOO_MANY_CMDS: The network BIOS command limit has been reached.")// ERROR_TOO_MANY_CMDS
        ERR(57L, "ERROR_ADAP_HDW_ERR: A network adapter hardware error occurred.")// ERROR_ADAP_HDW_ERR
        ERR(58L, "ERROR_BAD_NET_RESP: The specified server cannot perform the requested operation.")// ERROR_BAD_NET_RESP
        ERR(59L, "ERROR_UNEXP_NET_ERR: An unexpected network error occurred.")// ERROR_UNEXP_NET_ERR
        ERR(60L, "ERROR_BAD_REM_ADAP: The remote adapter is not compatible.")// ERROR_BAD_REM_ADAP
        ERR(61L, "ERROR_PRINTQ_FULL: The printer queue is full.")// ERROR_PRINTQ_FULL
        ERR(62L, "ERROR_NO_SPOOL_SPACE: Space to store the file waiting to be printed is not available on the server.")// ERROR_NO_SPOOL_SPACE
        ERR(63L, "ERROR_PRINT_CANCELLED: Your file waiting to be printed was deleted.")// ERROR_PRINT_CANCELLED
        ERR(64L, "ERROR_NETNAME_DELETED: The specified network name is no longer available.")// ERROR_NETNAME_DELETED
        ERR(65L, "ERROR_NETWORK_ACCESS_DENIED: Network access is denied.")// ERROR_NETWORK_ACCESS_DENIED
        ERR(66L, "ERROR_BAD_DEV_TYPE: The network resource type is not correct.")// ERROR_BAD_DEV_TYPE
        ERR(67L, "ERROR_BAD_NET_NAME: The network name cannot be found.")// ERROR_BAD_NET_NAME
        ERR(68L, "ERROR_TOO_MANY_NAMES: The name limit for the local computer network adapter card was exceeded.")// ERROR_TOO_MANY_NAMES
        ERR(69L, "ERROR_TOO_MANY_SESS: The network BIOS session limit was exceeded.")// ERROR_TOO_MANY_SESS
        ERR(70L, "ERROR_SHARING_PAUSED: The remote server has been paused or is in the process of being started.")// ERROR_SHARING_PAUSED
        ERR(71L, "ERROR_REQ_NOT_ACCEP: No more connections can be made to this remote computer at this time because there are already as many connections as the computer can accept.")// ERROR_REQ_NOT_ACCEP
        ERR(72L, "ERROR_REDIR_PAUSED: The specified printer or disk device has been paused.")// ERROR_REDIR_PAUSED
        ERR(80L, "ERROR_FILE_EXISTS: The file exists.")// ERROR_FILE_EXISTS
        ERR(82L, "ERROR_CANNOT_MAKE: The directory or file cannot be created.")// ERROR_CANNOT_MAKE
        ERR(83L, "ERROR_FAIL_I24: Fail on INT 24.")// ERROR_FAIL_I24
        ERR(84L, "ERROR_OUT_OF_STRUCTURES: Storage to process this request is not available.")// ERROR_OUT_OF_STRUCTURES
        ERR(85L, "ERROR_ALREADY_ASSIGNED: The local device name is already in use.")// ERROR_ALREADY_ASSIGNED
        ERR(86L, "ERROR_INVALID_PASSWORD: The specified network password is not correct.")// ERROR_INVALID_PASSWORD
        ERR(87L , "ERROR_INVALID_PARAMETER: The parameter is incorrect.")// ERROR_INVALID_PARAMETER
        ERR(88L, "ERROR_NET_WRITE_FAULT: A write fault occurred on the network.")// ERROR_NET_WRITE_FAULT
        ERR(89L, "ERROR_NO_PROC_SLOTS: The system cannot start another process at this time.")// ERROR_NO_PROC_SLOTS
        ERR(100L, "ERROR_TOO_MANY_SEMAPHORES: Cannot create another system semaphore.")// ERROR_TOO_MANY_SEMAPHORES
        ERR(101L, "ERROR_EXCL_SEM_ALREADY_OWNED: The exclusive semaphore is owned by another process.")// ERROR_EXCL_SEM_ALREADY_OWNED
        ERR(102L, "ERROR_SEM_IS_SET: The semaphore is set and cannot be closed.")// ERROR_SEM_IS_SET
        ERR(103L, "ERROR_TOO_MANY_SEM_REQUESTS: The semaphore cannot be set again.")// ERROR_TOO_MANY_SEM_REQUESTS
        ERR(104L, "ERROR_INVALID_AT_INTERRUPT_TIME: Cannot request exclusive semaphores at interrupt time.")// ERROR_INVALID_AT_INTERRUPT_TIME
        ERR(105L, "ERROR_SEM_OWNER_DIED: The previous ownership of this semaphore has ended.")// ERROR_SEM_OWNER_DIED
        ERR(106L, "ERROR_SEM_USER_LIMIT: Insert the diskette for drive %1.")// ERROR_SEM_USER_LIMIT
        ERR(107L, "ERROR_DISK_CHANGE: The program stopped because an alternate diskette was not inserted.")// ERROR_DISK_CHANGE
        ERR(108L, "ERROR_DRIVE_LOCKED: The disk is in use or locked by")// ERROR_DRIVE_LOCKED
        ERR(109L, "ERROR_BROKEN_PIPE: The pipe has been ended.")// ERROR_BROKEN_PIPE
        ERR(110L, "ERROR_OPEN_FAILED: The system cannot open the")// ERROR_OPEN_FAILED
        ERR(111L, "ERROR_BUFFER_OVERFLOW: The file name is too long.")// ERROR_BUFFER_OVERFLOW
        ERR(112L, "ERROR_DISK_FULL: There is not enough space on the disk.")// ERROR_DISK_FULL
        ERR(113L, "ERROR_NO_MORE_SEARCH_HANDLES: No more internal file identifiers available.")// ERROR_NO_MORE_SEARCH_HANDLES
        ERR(114L, "ERROR_INVALID_TARGET_HANDLE: The target internal file identifier is incorrect.")// ERROR_INVALID_TARGET_HANDLE
        ERR(117L, "ERROR_INVALID_CATEGORY: The IOCTL call made by the application program is not correct.")// ERROR_INVALID_CATEGORY
        ERR(118L, "ERROR_INVALID_VERIFY_SWITCH: The verify-on-write switch parameter value is not correct.")// ERROR_INVALID_VERIFY_SWITCH
        ERR(119L, "ERROR_BAD_DRIVER_LEVEL: The system does not support the command requested.")// ERROR_BAD_DRIVER_LEVEL
        ERR(120L, "ERROR_CALL_NOT_IMPLEMENTED: This function is not supported on this system.")// ERROR_CALL_NOT_IMPLEMENTED
        ERR(121L, "ERROR_SEM_TIMEOUT: The semaphore timeout period has expired.")// ERROR_SEM_TIMEOUT
        ERR(122L , "ERROR_INSUFFICIENT_BUFFER: The data area passed to a system call is too small.")// ERROR_INSUFFICIENT_BUFFER
        ERR(123L , "ERROR_INVALID_NAME: The filename, directory name, or volume label syntax is incorrect.")// ERROR_INVALID_NAME
        ERR(124L, "ERROR_INVALID_LEVEL: The system call level is not correct.")// ERROR_INVALID_LEVEL
        ERR(125L, "ERROR_NO_VOLUME_LABEL: The disk has no volume label.")// ERROR_NO_VOLUME_LABEL
        ERR(126L, "ERROR_MOD_NOT_FOUND: The specified module could not be found.")// ERROR_MOD_NOT_FOUND
        ERR(127L, "ERROR_PROC_NOT_FOUND: The specified procedure could not be found.")// ERROR_PROC_NOT_FOUND
        ERR(128L, "ERROR_WAIT_NO_CHILDREN: There are no child processes to wait for.")// ERROR_WAIT_NO_CHILDREN
        ERR(129L, "ERROR_CHILD_NOT_COMPLETE: The %1 application cannot be run in Win32 mode.")// ERROR_CHILD_NOT_COMPLETE
        ERR(130L, "ERROR_DIRECT_ACCESS_HANDLE: Attempt to use a file handle to an open disk partition for an operation other than raw disk I/O.")// ERROR_DIRECT_ACCESS_HANDLE
        ERR(131L, "ERROR_NEGATIVE_SEEK: An attempt was made to move the file pointer before the beginning of the file.")// ERROR_NEGATIVE_SEEK
        ERR(132L, "ERROR_SEEK_ON_DEVICE: The file pointer cannot be set on the specified device or file.")// ERROR_SEEK_ON_DEVICE
        ERR(133L, "ERROR_IS_JOIN_TARGET: A JOIN or SUBST command cannot be used for a drive that contains previously joined drives.")// ERROR_IS_JOIN_TARGET
        ERR(134L, "ERROR_IS_JOINED: An attempt was made to use a JOIN or SUBST command on a drive that has already been joined.")// ERROR_IS_JOINED
        ERR(135L, "ERROR_IS_SUBSTED: An attempt was made to use a JOIN or SUBST command on a drive that has already been substituted.")// ERROR_IS_SUBSTED
        ERR(136L, "ERROR_NOT_JOINED: The system tried to delete the JOIN of a drive that is not joined.")// ERROR_NOT_JOINED
        ERR(137L, "ERROR_NOT_SUBSTED: The system tried to delete the substitution of a drive that is not substituted.")// ERROR_NOT_SUBSTED
        ERR(138L, "ERROR_JOIN_TO_JOIN: The system tried to join a drive to a directory on a joined drive.")// ERROR_JOIN_TO_JOIN
        ERR(139L, "ERROR_SUBST_TO_SUBST: The system tried to substitute a drive to a directory on a substituted drive.")// ERROR_SUBST_TO_SUBST
        ERR(140L, "ERROR_JOIN_TO_SUBST: The system tried to join a drive to a directory on a substituted drive.")// ERROR_JOIN_TO_SUBST
        ERR(141L, "ERROR_SUBST_TO_JOIN: The system tried to SUBST a drive to a directory on a joined drive.")// ERROR_SUBST_TO_JOIN
        ERR(142L, "ERROR_BUSY_DRIVE: The system cannot perform a JOIN or SUBST at this time.")// ERROR_BUSY_DRIVE
        ERR(143L, "ERROR_SAME_DRIVE: The system cannot join or substitute a drive to or for a directory on the same drive.")// ERROR_SAME_DRIVE
        ERR(144L, "ERROR_DIR_NOT_ROOT: The directory is not a subdirectory of the root directory.")// ERROR_DIR_NOT_ROOT
        ERR(145L, "ERROR_DIR_NOT_EMPTY: The directory is not empty.")// ERROR_DIR_NOT_EMPTY
        ERR(146L, "ERROR_IS_SUBST_PATH: The path specified is being used in a substitute.")// ERROR_IS_SUBST_PATH
        ERR(147L, "ERROR_IS_JOIN_PATH: Not enough resources are available to process this command.")// ERROR_IS_JOIN_PATH
        ERR(148L, "ERROR_PATH_BUSY: The path specified cannot be used at this time.")// ERROR_PATH_BUSY
        ERR(149L, "ERROR_IS_SUBST_TARGET: An attempt was made to join or substitute a drive for which a directory on the drive is the target of a previous substitute.")// ERROR_IS_SUBST_TARGET
        ERR(150L, "ERROR_SYSTEM_TRACE: System trace information was not specified in your CONFIG.SYS file, or tracing is disallowed.")// ERROR_SYSTEM_TRACE
        ERR(151L, "ERROR_INVALID_EVENT_COUNT: The number of specified semaphore events for DosMuxSemWait is not correct.")// ERROR_INVALID_EVENT_COUNT
        ERR(152L, "ERROR_TOO_MANY_MUXWAITERS: DosMuxSemWait did not execute; too many semaphores are already set.")// ERROR_TOO_MANY_MUXWAITERS
        ERR(153L, "ERROR_INVALID_LIST_FORMAT: The DosMuxSemWait list is not correct.")// ERROR_INVALID_LIST_FORMAT
        ERR(154L, "ERROR_LABEL_TOO_LONG: The volume label you entered exceeds the label character")// ERROR_LABEL_TOO_LONG
        ERR(155L, "ERROR_TOO_MANY_TCBS: Cannot create another thread.")// ERROR_TOO_MANY_TCBS
        ERR(156L, "ERROR_SIGNAL_REFUSED: The recipient process has refused the signal.")// ERROR_SIGNAL_REFUSED
        ERR(157L, "ERROR_DISCARDED: The segment is already discarded and cannot be locked.")// ERROR_DISCARDED
        ERR(158L, "ERROR_NOT_LOCKED: The segment is already unlocked.")// ERROR_NOT_LOCKED
        ERR(159L, "ERROR_BAD_THREADID_ADDR: The address for the thread ID is not correct.")// ERROR_BAD_THREADID_ADDR
        ERR(160L, "ERROR_BAD_ARGUMENTS: The argument string passed to DosExecPgm is not correct.")// ERROR_BAD_ARGUMENTS
        ERR(161L, "ERROR_BAD_PATHNAME: The specified path is invalid.")// ERROR_BAD_PATHNAME
        ERR(162L, "ERROR_SIGNAL_PENDING: A signal is already pending.")// ERROR_SIGNAL_PENDING
        ERR(164L, "ERROR_MAX_THRDS_REACHED: No more threads can be created in the system.")// ERROR_MAX_THRDS_REACHED
        ERR(167L, "ERROR_LOCK_FAILED: Unable to lock a region of a file.")// ERROR_LOCK_FAILED
        ERR(170L , "ERROR_BUSY: The requested resource is in use.")// ERROR_BUSY
        ERR(173L, "ERROR_CANCEL_VIOLATION: A lock request was not outstanding for the supplied cancel region.")// ERROR_CANCEL_VIOLATION
        ERR(174L, "ERROR_ATOMIC_LOCKS_NOT_SUPPORTED: The file system does not support atomic changes to the lock type.")// ERROR_ATOMIC_LOCKS_NOT_SUPPORTED
        ERR(180L, "ERROR_INVALID_SEGMENT_NUMBER: The system detected a segment number that was not correct.")// ERROR_INVALID_SEGMENT_NUMBER
        ERR(182L, "ERROR_INVALID_ORDINAL: The operating system cannot run %1.")// ERROR_INVALID_ORDINAL
        ERR(183L, "ERROR_ALREADY_EXISTS: Cannot create a file when that file already exists.")// ERROR_ALREADY_EXISTS
        ERR(186L, "ERROR_INVALID_FLAG_NUMBER: The flag passed is not correct.")// ERROR_INVALID_FLAG_NUMBER
        ERR(187L, "ERROR_SEM_NOT_FOUND: The specified system semaphore name was not found.")// ERROR_SEM_NOT_FOUND
        ERR(188L, "ERROR_INVALID_STARTING_CODESEG: The operating system cannot run %1.")// ERROR_INVALID_STARTING_CODESEG
        ERR(189L, "ERROR_INVALID_STACKSEG: The operating system cannot run %1.")// ERROR_INVALID_STACKSEG
        ERR(190L, "ERROR_INVALID_MODULETYPE: The operating system cannot run %1.")// ERROR_INVALID_MODULETYPE
        ERR(191L, "ERROR_INVALID_EXE_SIGNATURE: Cannot run %1 in Win32 mode.")// ERROR_INVALID_EXE_SIGNATURE
        ERR(192L, "ERROR_EXE_MARKED_INVALID: The operating system cannot run %1.")// ERROR_EXE_MARKED_INVALID
        ERR(193L, "ERROR_BAD_EXE_FORMAT: %1 is not a valid Win32 application.")// ERROR_BAD_EXE_FORMAT
        ERR(194L, "ERROR_ITERATED_DATA_EXCEEDS_64k: The operating system cannot run %1.")// ERROR_ITERATED_DATA_EXCEEDS_64k
        ERR(195L, "ERROR_INVALID_MINALLOCSIZE: The operating system cannot run %1.")// ERROR_INVALID_MINALLOCSIZE
        ERR(196L, "ERROR_DYNLINK_FROM_INVALID_RING: The operating system cannot run this application program.")// ERROR_DYNLINK_FROM_INVALID_RING
        ERR(197L, "ERROR_IOPL_NOT_ENABLED: The operating system is not presently configured to run this application.")// ERROR_IOPL_NOT_ENABLED
        ERR(198L, "ERROR_INVALID_SEGDPL: The operating system cannot run %1.")// ERROR_INVALID_SEGDPL
        ERR(199L, "ERROR_AUTODATASEG_EXCEEDS_64k: The operating system cannot run this application program.")// ERROR_AUTODATASEG_EXCEEDS_64k
        ERR(200L, "ERROR_RING2SEG_MUST_BE_MOVABLE: The code segment cannot be greater than or equal to 64K.")// ERROR_RING2SEG_MUST_BE_MOVABLE
        ERR(201L, "ERROR_RELOC_CHAIN_XEEDS_SEGLIM: The operating system cannot run %1.")// ERROR_RELOC_CHAIN_XEEDS_SEGLIM
        ERR(202L, "ERROR_INFLOOP_IN_RELOC_CHAIN: The operating system cannot run %1.")// ERROR_INFLOOP_IN_RELOC_CHAIN
        ERR(203L, "ERROR_ENVVAR_NOT_FOUND: The system could not find the environment")// ERROR_ENVVAR_NOT_FOUND
        ERR(205L, "ERROR_NO_SIGNAL_SENT: No process in the command subtree has a")// ERROR_NO_SIGNAL_SENT
        ERR(206L, "ERROR_FILENAME_EXCED_RANGE: The filename or extension is too long.")// ERROR_FILENAME_EXCED_RANGE
        ERR(207L, "ERROR_RING2_STACK_IN_USE: The ring 2 stack is in use.")// ERROR_RING2_STACK_IN_USE
        ERR(208L, "ERROR_META_EXPANSION_TOO_LONG: The global filename characters, * or ?, are entered incorrectly or too many global filename characters are specified.")// ERROR_META_EXPANSION_TOO_LONG
        ERR(209L, "ERROR_INVALID_SIGNAL_NUMBER: The signal being posted is not correct.")// ERROR_INVALID_SIGNAL_NUMBER
        ERR(210L, "ERROR_THREAD_1_INACTIVE: The signal handler cannot be set.")// ERROR_THREAD_1_INACTIVE
        ERR(212L, "ERROR_LOCKED: The segment is locked and cannot be reallocated.")// ERROR_LOCKED
        ERR(214L, "ERROR_TOO_MANY_MODULES: Too many dynamic-link modules are attached to this program or dynamic-link module.")// ERROR_TOO_MANY_MODULES
        ERR(215L, "ERROR_NESTING_NOT_ALLOWED: Cannot nest calls to LoadModule.")// ERROR_NESTING_NOT_ALLOWED
        ERR(216L, "ERROR_EXE_MACHINE_TYPE_MISMATCH: The image file %1 is valid, but is for a machine type other than the current machine.")// ERROR_EXE_MACHINE_TYPE_MISMATCH
        ERR(230L, "ERROR_BAD_PIPE: The pipe state is invalid.")// ERROR_BAD_PIPE
        ERR(231L, "ERROR_PIPE_BUSY: All pipe instances are busy.")// ERROR_PIPE_BUSY
        ERR(232L, "ERROR_NO_DATA: The pipe is being closed.")// ERROR_NO_DATA
        ERR(233L, "ERROR_PIPE_NOT_CONNECTED: No process is on the other end of the pipe.")// ERROR_PIPE_NOT_CONNECTED
        ERR(234L , "ERROR_MORE_DATA: More data is available.")// ERROR_MORE_DATA
        ERR(240L, "ERROR_VC_DISCONNECTED: The session was canceled.")// ERROR_VC_DISCONNECTED
        ERR(254L, "ERROR_INVALID_EA_NAME: The specified extended attribute name was invalid.")// ERROR_INVALID_EA_NAME
        ERR(255L, "ERROR_EA_LIST_INCONSISTENT: The extended attributes are inconsistent.")// ERROR_EA_LIST_INCONSISTENT
        ERR(258L , "WAIT_TIMEOUT: The wait operation timed out.")// WAIT_TIMEOUT
        ERR(259L, "ERROR_NO_MORE_ITEMS: No more data is available.")// ERROR_NO_MORE_ITEMS
        ERR(266L, "ERROR_CANNOT_COPY: The copy functions cannot be used.")// ERROR_CANNOT_COPY
        ERR(267L, "ERROR_DIRECTORY: The directory name is invalid.")// ERROR_DIRECTORY
        ERR(275L, "ERROR_EAS_DIDNT_FIT: The extended attributes did not fit in the buffer.")// ERROR_EAS_DIDNT_FIT
        ERR(276L, "ERROR_EA_FILE_CORRUPT: The extended attribute file on the mounted file system is corrupt.")// ERROR_EA_FILE_CORRUPT
        ERR(277L, "ERROR_EA_TABLE_FULL: The extended attribute table file is full.")// ERROR_EA_TABLE_FULL
        ERR(278L, "ERROR_INVALID_EA_HANDLE: The specified extended attribute handle is invalid.")// ERROR_INVALID_EA_HANDLE
        ERR(282L, "ERROR_EAS_NOT_SUPPORTED: The mounted file system does not support extended attributes.")// ERROR_EAS_NOT_SUPPORTED
        ERR(288L, "ERROR_NOT_OWNER: Attempt to release mutex not owned by caller.")// ERROR_NOT_OWNER
        ERR(298L, "ERROR_TOO_MANY_POSTS: Too many posts were made to a semaphore.")// ERROR_TOO_MANY_POSTS
        ERR(299L, "ERROR_PARTIAL_COPY: Only part of a ReadProcessMemory or WriteProcessMemory request was completed.")// ERROR_PARTIAL_COPY
        ERR(300L, "ERROR_OPLOCK_NOT_GRANTED: The oplock request is denied.")// ERROR_OPLOCK_NOT_GRANTED
        ERR(301L, "ERROR_INVALID_OPLOCK_PROTOCOL: An invalid oplock acknowledgment was received by the system.")// ERROR_INVALID_OPLOCK_PROTOCOL
        ERR(302L, "ERROR_DISK_TOO_FRAGMENTED: The volume is too fragmented to complete this operation.")// ERROR_DISK_TOO_FRAGMENTED
        ERR(317L, "ERROR_MR_MID_NOT_FOUND: The system cannot find message text for message number 0x%1 in the message file for %2.")// ERROR_MR_MID_NOT_FOUND
        ERR(487L, "ERROR_INVALID_ADDRESS: Attempt to access invalid address.")// ERROR_INVALID_ADDRESS
        ERR(534L, "ERROR_ARITHMETIC_OVERFLOW: Arithmetic result exceeded 32 bits.")// ERROR_ARITHMETIC_OVERFLOW
        ERR(535L, "ERROR_PIPE_CONNECTED: There is a process on other end of the pipe.")// ERROR_PIPE_CONNECTED
        ERR(536L, "ERROR_PIPE_LISTENING: Waiting for a process to open the other end of the pipe.")// ERROR_PIPE_LISTENING
        ERR(994L, "ERROR_EA_ACCESS_DENIED: Access to the extended attribute was denied.")// ERROR_EA_ACCESS_DENIED
        ERR(995L, "ERROR_OPERATION_ABORTED: The I/O operation has been aborted because of either a thread exit or an application request.")// ERROR_OPERATION_ABORTED
        ERR(996L, "ERROR_IO_INCOMPLETE: Overlapped I/O event is not in a signaled state.")// ERROR_IO_INCOMPLETE
        ERR(997L , "ERROR_IO_PENDING: Overlapped I/O operation is in progress.")// ERROR_IO_PENDING
        ERR(998L, "ERROR_NOACCESS: Invalid access to memory location.")// ERROR_NOACCESS
        ERR(999L, "ERROR_SWAPERROR: Error performing inpage operation.")// ERROR_SWAPERROR
        ERR(1001L, "ERROR_STACK_OVERFLOW: Recursion too deep; the stack overflowed.")// ERROR_STACK_OVERFLOW
        ERR(1002L, "ERROR_INVALID_MESSAGE: The window cannot act on the sent message.")// ERROR_INVALID_MESSAGE
        ERR(1003L, "ERROR_CAN_NOT_COMPLETE: Cannot complete this function.")// ERROR_CAN_NOT_COMPLETE
        ERR(1004L, "ERROR_INVALID_FLAGS: Invalid flags.")// ERROR_INVALID_FLAGS
        ERR(1005L, "ERROR_UNRECOGNIZED_VOLUME: The volume does not contain a recognized file system.")// ERROR_UNRECOGNIZED_VOLUME
        ERR(1006L, "ERROR_FILE_INVALID: The volume for a file has been externally altered so that the opened file is no longer valid.")// ERROR_FILE_INVALID
        ERR(1007L, "ERROR_FULLSCREEN_MODE: The requested operation cannot be performed in full-screen mode.")// ERROR_FULLSCREEN_MODE
        ERR(1008L, "ERROR_NO_TOKEN: An attempt was made to reference a token that does not exist.")// ERROR_NO_TOKEN
        ERR(1009L, "ERROR_BADDB: The configuration registry database is corrupt.")// ERROR_BADDB
        ERR(1010L, "ERROR_BADKEY: The configuration registry key is invalid.")// ERROR_BADKEY
        ERR(1011L, "ERROR_CANTOPEN: The configuration registry key could not be opened.")// ERROR_CANTOPEN
        ERR(1012L, "ERROR_CANTREAD: The configuration registry key could not be read.")// ERROR_CANTREAD
        ERR(1013L, "ERROR_CANTWRITE: The configuration registry key could not be written.")// ERROR_CANTWRITE
        ERR(1014L, "ERROR_REGISTRY_RECOVERED: One of the files in the registry database had to be recovered by use of a log or alternate copy. The recovery was successful.")// ERROR_REGISTRY_RECOVERED
        ERR(1015L, "ERROR_REGISTRY_CORRUPT: The registry is corrupted. The structure of one of the files containing registry data is corrupted, or the system's memory image of the file is corrupted, or the file could not be recovered because the alternate copy or log was absent or corrupted.")// ERROR_REGISTRY_CORRUPT
        ERR(1016L, "ERROR_REGISTRY_IO_FAILED: An I/O operation initiated by the registry failed unrecoverably. The registry could not read in, or write out, or flush, one of the files that contain the system's image of the registry.")// ERROR_REGISTRY_IO_FAILED
        ERR(1017L, "ERROR_NOT_REGISTRY_FILE: The system has attempted to load or restore a file into the registry, but the specified file is not in a registry file format.")// ERROR_NOT_REGISTRY_FILE
        ERR(1018L, "ERROR_KEY_DELETED: Illegal operation attempted on a registry key that has been marked for deletion.")// ERROR_KEY_DELETED
        ERR(1019L, "ERROR_NO_LOG_SPACE: System could not allocate the required space in a registry log.")// ERROR_NO_LOG_SPACE
        ERR(1020L, "ERROR_KEY_HAS_CHILDREN: Cannot create a symbolic link in a registry key that already has subkeys or values.")// ERROR_KEY_HAS_CHILDREN
        ERR(1021L, "ERROR_CHILD_MUST_BE_VOLATILE: Cannot create a stable subkey under a volatile parent key.")// ERROR_CHILD_MUST_BE_VOLATILE
        ERR(1022L, "ERROR_NOTIFY_ENUM_DIR: A notify change request is being completed and the information is not being returned in the caller's buffer. The caller now needs to enumerate the files to find the changes.")// ERROR_NOTIFY_ENUM_DIR
        ERR(1051L, "ERROR_DEPENDENT_SERVICES_RUNNING: A stop control has been sent to a service that other running services are dependent on.")// ERROR_DEPENDENT_SERVICES_RUNNING
        ERR(1052L, "ERROR_INVALID_SERVICE_CONTROL: The requested control is not valid for this service.")// ERROR_INVALID_SERVICE_CONTROL
        ERR(1053L, "ERROR_SERVICE_REQUEST_TIMEOUT: The service did not respond to the start or control request in a timely fashion.")// ERROR_SERVICE_REQUEST_TIMEOUT
        ERR(1054L, "ERROR_SERVICE_NO_THREAD: A thread could not be created for the service.")// ERROR_SERVICE_NO_THREAD
        ERR(1055L, "ERROR_SERVICE_DATABASE_LOCKED: The service database is locked.")// ERROR_SERVICE_DATABASE_LOCKED
        ERR(1056L, "ERROR_SERVICE_ALREADY_RUNNING: An instance of the service is already running.")// ERROR_SERVICE_ALREADY_RUNNING
        ERR(1057L, "ERROR_INVALID_SERVICE_ACCOUNT: The account name is invalid or does not exist, or the password is invalid for the account name specified.")// ERROR_INVALID_SERVICE_ACCOUNT
        ERR(1058L, "ERROR_SERVICE_DISABLED: The service cannot be started, either because it is disabled or because it has no enabled devices associated with it.")// ERROR_SERVICE_DISABLED
        ERR(1059L, "ERROR_CIRCULAR_DEPENDENCY: Circular service dependency was specified.")// ERROR_CIRCULAR_DEPENDENCY
        ERR(1060L, "ERROR_SERVICE_DOES_NOT_EXIST: The specified service does not exist as an installed service.")// ERROR_SERVICE_DOES_NOT_EXIST
        ERR(1061L, "ERROR_SERVICE_CANNOT_ACCEPT_CTRL: The service cannot accept control messages at this time.")// ERROR_SERVICE_CANNOT_ACCEPT_CTRL
        ERR(1062L, "ERROR_SERVICE_NOT_ACTIVE: The service has not been started.")// ERROR_SERVICE_NOT_ACTIVE
        ERR(1063L, "ERROR_FAILED_SERVICE_CONTROLLER_CONNECT: The service process could not connect to the service controller.")// ERROR_FAILED_SERVICE_CONTROLLER_CONNECT
        ERR(1064L, "ERROR_EXCEPTION_IN_SERVICE: An exception occurred in the service when handling the control request.")// ERROR_EXCEPTION_IN_SERVICE
        ERR(1065L, "ERROR_DATABASE_DOES_NOT_EXIST: The database specified does not exist.")// ERROR_DATABASE_DOES_NOT_EXIST
        ERR(1066L, "ERROR_SERVICE_SPECIFIC_ERROR: The service has returned a service-specific error code.")// ERROR_SERVICE_SPECIFIC_ERROR
        ERR(1067L, "ERROR_PROCESS_ABORTED: The process terminated unexpectedly.")// ERROR_PROCESS_ABORTED
        ERR(1068L, "ERROR_SERVICE_DEPENDENCY_FAIL: The dependency service or group failed to start.")// ERROR_SERVICE_DEPENDENCY_FAIL
        ERR(1069L, "ERROR_SERVICE_LOGON_FAILED: The service did not start due to a logon failure.")// ERROR_SERVICE_LOGON_FAILED
        ERR(1070L, "ERROR_SERVICE_START_HANG: After starting, the service hung in a start-pending state.")// ERROR_SERVICE_START_HANG
        ERR(1071L, "ERROR_INVALID_SERVICE_LOCK: The specified service database lock is invalid.")// ERROR_INVALID_SERVICE_LOCK
        ERR(1072L, "ERROR_SERVICE_MARKED_FOR_DELETE: The specified service has been marked for deletion.")// ERROR_SERVICE_MARKED_FOR_DELETE
        ERR(1073L, "ERROR_SERVICE_EXISTS: The specified service already exists.")// ERROR_SERVICE_EXISTS
        ERR(1074L, "ERROR_ALREADY_RUNNING_LKG: The system is currently running with the last-known-good configuration.")// ERROR_ALREADY_RUNNING_LKG
        ERR(1075L, "ERROR_SERVICE_DEPENDENCY_DELETED: The dependency service does not exist or has been marked for deletion.")// ERROR_SERVICE_DEPENDENCY_DELETED
        ERR(1076L, "ERROR_BOOT_ALREADY_ACCEPTED: The current boot has already been accepted for use as the last-known-good control set.")// ERROR_BOOT_ALREADY_ACCEPTED
        ERR(1077L, "ERROR_SERVICE_NEVER_STARTED: No attempts to start the service have been made since the last boot.")// ERROR_SERVICE_NEVER_STARTED
        ERR(1078L, "ERROR_DUPLICATE_SERVICE_NAME: The name is already in use as either a service name or a service display name.")// ERROR_DUPLICATE_SERVICE_NAME
        ERR(1079L, "ERROR_DIFFERENT_SERVICE_ACCOUNT: The account specified for this service is different from the account specified for other services running in the same process.")// ERROR_DIFFERENT_SERVICE_ACCOUNT
        ERR(1080L, "ERROR_CANNOT_DETECT_DRIVER_FAILURE: Failure actions can only be set for Win32 services, not for drivers.")// ERROR_CANNOT_DETECT_DRIVER_FAILURE
        ERR(1081L, "ERROR_CANNOT_DETECT_PROCESS_ABORT: This service runs in the same process as the service control manager.")// ERROR_CANNOT_DETECT_PROCESS_ABORT
        ERR(1082L, "ERROR_NO_RECOVERY_PROGRAM: No recovery program has been configured for this service.")// ERROR_NO_RECOVERY_PROGRAM
        ERR(1083L, "ERROR_SERVICE_NOT_IN_EXE: The executable program that this service is configured to run in does not implement the service.")// ERROR_SERVICE_NOT_IN_EXE
        ERR(1084L, "ERROR_NOT_SAFEBOOT_SERVICE: This service cannot be started in Safe Mode")// ERROR_NOT_SAFEBOOT_SERVICE
        ERR(1100L, "ERROR_END_OF_MEDIA: The physical end of the tape has been reached.")// ERROR_END_OF_MEDIA
        ERR(1101L, "ERROR_FILEMARK_DETECTED: A tape access reached a filemark.")// ERROR_FILEMARK_DETECTED
        ERR(1102L, "ERROR_BEGINNING_OF_MEDIA: The beginning of the tape or a partition was encountered.")// ERROR_BEGINNING_OF_MEDIA
        ERR(1103L, "ERROR_SETMARK_DETECTED: A tape access reached the end of a set of files.")// ERROR_SETMARK_DETECTED
        ERR(1104L, "ERROR_NO_DATA_DETECTED: No more data is on the tape.")// ERROR_NO_DATA_DETECTED
        ERR(1105L, "ERROR_PARTITION_FAILURE: Tape could not be partitioned.")// ERROR_PARTITION_FAILURE
        ERR(1106L, "ERROR_INVALID_BLOCK_LENGTH: When accessing a new tape of a multivolume partition, the current block size is incorrect.")// ERROR_INVALID_BLOCK_LENGTH
        ERR(1107L, "ERROR_DEVICE_NOT_PARTITIONED: Tape partition information could not be found when loading a tape.")// ERROR_DEVICE_NOT_PARTITIONED
        ERR(1108L, "ERROR_UNABLE_TO_LOCK_MEDIA: Unable to lock the media eject mechanism.")// ERROR_UNABLE_TO_LOCK_MEDIA
        ERR(1109L, "ERROR_UNABLE_TO_UNLOAD_MEDIA: Unable to unload the media.")// ERROR_UNABLE_TO_UNLOAD_MEDIA
        ERR(1110L, "ERROR_MEDIA_CHANGED: The media in the drive may have changed.")// ERROR_MEDIA_CHANGED
        ERR(1111L, "ERROR_BUS_RESET: The I/O bus was reset.")// ERROR_BUS_RESET
        ERR(1112L, "ERROR_NO_MEDIA_IN_DRIVE: No media in drive.")// ERROR_NO_MEDIA_IN_DRIVE
        ERR(1113L, "ERROR_NO_UNICODE_TRANSLATION: No mapping for the Unicode character exists in the target multi-byte code page.")// ERROR_NO_UNICODE_TRANSLATION
        ERR(1114L, "ERROR_DLL_INIT_FAILED: A dynamic link library (DLL) initialization routine failed.")// ERROR_DLL_INIT_FAILED
        ERR(1115L, "ERROR_SHUTDOWN_IN_PROGRESS: A system shutdown is in progress.")// ERROR_SHUTDOWN_IN_PROGRESS
        ERR(1116L, "ERROR_NO_SHUTDOWN_IN_PROGRESS: Unable to abort the system shutdown because no shutdown was in progress.")// ERROR_NO_SHUTDOWN_IN_PROGRESS
        ERR(1117L, "ERROR_IO_DEVICE: The request could not be performed because of an I/O device error.")// ERROR_IO_DEVICE
        ERR(1118L, "ERROR_SERIAL_NO_DEVICE: No serial device was successfully initialized. The serial driver will unload.")// ERROR_SERIAL_NO_DEVICE
        ERR(1119L, "ERROR_IRQ_BUSY: Unable to open a device that was sharing an interrupt request (IRQ) with other devices. At least one other device that uses that IRQ was already opened.")// ERROR_IRQ_BUSY
        ERR(1120L, "ERROR_MORE_WRITES: A serial I/O operation was completed by another write to the serial port.")// ERROR_MORE_WRITES
        ERR(1121L, "ERROR_COUNTER_TIMEOUT: A serial I/O operation completed because the timeout period expired.")// ERROR_COUNTER_TIMEOUT
        ERR(1122L, "ERROR_FLOPPY_ID_MARK_NOT_FOUND: No ID address mark was found on the floppy disk.")// ERROR_FLOPPY_ID_MARK_NOT_FOUND
        ERR(1123L, "ERROR_FLOPPY_WRONG_CYLINDER: Mismatch between the floppy disk sector ID field and the floppy disk controller track address.")// ERROR_FLOPPY_WRONG_CYLINDER
        ERR(1124L, "ERROR_FLOPPY_UNKNOWN_ERROR: The floppy disk controller reported an error that is not recognized by the floppy disk driver.")// ERROR_FLOPPY_UNKNOWN_ERROR
        ERR(1125L, "ERROR_FLOPPY_BAD_REGISTERS: The floppy disk controller returned inconsistent results in its registers.")// ERROR_FLOPPY_BAD_REGISTERS
        ERR(1126L, "ERROR_DISK_RECALIBRATE_FAILED: While accessing the hard disk, a recalibrate operation failed, even after retries.")// ERROR_DISK_RECALIBRATE_FAILED
        ERR(1127L, "ERROR_DISK_OPERATION_FAILED: While accessing the hard disk, a disk operation failed even after retries.")// ERROR_DISK_OPERATION_FAILED
        ERR(1128L, "ERROR_DISK_RESET_FAILED: While accessing the hard disk, a disk controller reset was needed, but even that failed.")// ERROR_DISK_RESET_FAILED
        ERR(1129L, "ERROR_EOM_OVERFLOW: Physical end of tape encountered.")// ERROR_EOM_OVERFLOW
        ERR(1130L, "ERROR_NOT_ENOUGH_SERVER_MEMORY: Not enough server storage is available to process this command.")// ERROR_NOT_ENOUGH_SERVER_MEMORY
        ERR(1131L, "ERROR_POSSIBLE_DEADLOCK: A potential deadlock condition has been detected.")// ERROR_POSSIBLE_DEADLOCK
        ERR(1132L, "ERROR_MAPPED_ALIGNMENT: The base address or the file offset specified does not have the proper alignment.")// ERROR_MAPPED_ALIGNMENT
        ERR(1140L, "ERROR_SET_POWER_STATE_VETOED: An attempt to change the system power state was vetoed by another application or driver.")// ERROR_SET_POWER_STATE_VETOED
        ERR(1141L, "ERROR_SET_POWER_STATE_FAILED: The system BIOS failed an attempt to change the system power state.")// ERROR_SET_POWER_STATE_FAILED
        ERR(1142L, "ERROR_TOO_MANY_LINKS: An attempt was made to create more links on a file than the file system supports.")// ERROR_TOO_MANY_LINKS
        ERR(1150L, "ERROR_OLD_WIN_VERSION: The specified program requires a newer version of Windows.")// ERROR_OLD_WIN_VERSION
        ERR(1151L, "ERROR_APP_WRONG_OS: The specified program is not a Windows or MS-DOS program.")// ERROR_APP_WRONG_OS
        ERR(1152L, "ERROR_SINGLE_INSTANCE_APP: Cannot start more than one instance of the specified program.")// ERROR_SINGLE_INSTANCE_APP
        ERR(1153L, "ERROR_RMODE_APP: The specified program was written for an earlier version of Windows.")// ERROR_RMODE_APP
        ERR(1154L, "ERROR_INVALID_DLL: One of the library files needed to run this application is damaged.")// ERROR_INVALID_DLL
        ERR(1155L, "ERROR_NO_ASSOCIATION: No application is associated with the specified file for this operation.")// ERROR_NO_ASSOCIATION
        ERR(1156L, "ERROR_DDE_FAIL: An error occurred in sending the command to the application.")// ERROR_DDE_FAIL
        ERR(1157L, "ERROR_DLL_NOT_FOUND: One of the library files needed to run this application cannot be found.")// ERROR_DLL_NOT_FOUND
        ERR(1158L, "ERROR_NO_MORE_USER_HANDLES: The current process has used all of its system allowance of handles for Window Manager objects.")// ERROR_NO_MORE_USER_HANDLES
        ERR(1159L, "ERROR_MESSAGE_SYNC_ONLY: The message can be used only with synchronous operations.")// ERROR_MESSAGE_SYNC_ONLY
        ERR(1160L, "ERROR_SOURCE_ELEMENT_EMPTY: The indicated source element has no media.")// ERROR_SOURCE_ELEMENT_EMPTY
        ERR(1161L, "ERROR_DESTINATION_ELEMENT_FULL: The indicated destination element already contains media.")// ERROR_DESTINATION_ELEMENT_FULL
        ERR(1162L, "ERROR_ILLEGAL_ELEMENT_ADDRESS: The indicated element does not exist.")// ERROR_ILLEGAL_ELEMENT_ADDRESS
        ERR(1163L, "ERROR_MAGAZINE_NOT_PRESENT: The indicated element is part of a magazine that is not present.")// ERROR_MAGAZINE_NOT_PRESENT
        ERR(1164L , "ERROR_DEVICE_REINITIALIZATION_NEEDED: The indicated device requires reinitialization due to hardware errors.")// ERROR_DEVICE_REINITIALIZATION_NEEDED
        ERR(1165L, "ERROR_DEVICE_REQUIRES_CLEANING: The device has indicated that cleaning is required before further operations are attempted.")// ERROR_DEVICE_REQUIRES_CLEANING
        ERR(1166L, "ERROR_DEVICE_DOOR_OPEN: The device has indicated that its door is open.")// ERROR_DEVICE_DOOR_OPEN
        ERR(1167L, "ERROR_DEVICE_NOT_CONNECTED: The device is not connected.")// ERROR_DEVICE_NOT_CONNECTED
        ERR(1168L, "ERROR_NOT_FOUND: Element not found.")// ERROR_NOT_FOUND
        ERR(1169L, "ERROR_NO_MATCH: There was no match for the specified key in the index.")// ERROR_NO_MATCH
        ERR(1170L, "ERROR_SET_NOT_FOUND: The property set specified does not exist on the object.")// ERROR_SET_NOT_FOUND
        ERR(1171L, "ERROR_POINT_NOT_FOUND: The point passed to GetMouseMovePoints is not in the buffer.")// ERROR_POINT_NOT_FOUND
        ERR(1172L, "ERROR_NO_TRACKING_SERVICE: The tracking (workstation) service is not running.")// ERROR_NO_TRACKING_SERVICE
        ERR(1173L, "ERROR_NO_VOLUME_ID: The Volume ID could not be found.")// ERROR_NO_VOLUME_ID
        ERR(1175L, "ERROR_UNABLE_TO_REMOVE_REPLACED: Unable to remove the file to be replaced.")// ERROR_UNABLE_TO_REMOVE_REPLACED
        ERR(1176L, "ERROR_UNABLE_TO_MOVE_REPLACEMENT: Unable to move the replacement file to the file to be replaced. The file to be replaced has retained its original name.")// ERROR_UNABLE_TO_MOVE_REPLACEMENT
        ERR(1177L, "ERROR_UNABLE_TO_MOVE_REPLACEMENT_2: Unable to move the replacement file to the file to be replaced. The file to be replaced has been renamed using the backup name.")// ERROR_UNABLE_TO_MOVE_REPLACEMENT_2
        ERR(1178L, "ERROR_JOURNAL_DELETE_IN_PROGRESS: The volume change journal is being deleted.")// ERROR_JOURNAL_DELETE_IN_PROGRESS
        ERR(1179L, "ERROR_JOURNAL_NOT_ACTIVE: The volume change journal service is not active.")// ERROR_JOURNAL_NOT_ACTIVE
        ERR(1180L, "ERROR_POTENTIAL_FILE_FOUND: A file was found, but it may not be the correct file.")// ERROR_POTENTIAL_FILE_FOUND
        ERR(1181L, "ERROR_JOURNAL_ENTRY_DELETED: The journal entry has been deleted from the journal.")// ERROR_JOURNAL_ENTRY_DELETED
        ERR(1200L, "ERROR_BAD_DEVICE: The specified device name is invalid.")// ERROR_BAD_DEVICE
        ERR(1201L, "ERROR_CONNECTION_UNAVAIL: The device is not currently connected but it is a remembered connection.")// ERROR_CONNECTION_UNAVAIL
        ERR(1202L, "ERROR_DEVICE_ALREADY_REMEMBERED: The local device name has a remembered connection to another network resource.")// ERROR_DEVICE_ALREADY_REMEMBERED
        ERR(1203L, "ERROR_NO_NET_OR_BAD_PATH: No network provider accepted the given network path.")// ERROR_NO_NET_OR_BAD_PATH
        ERR(1204L, "ERROR_BAD_PROVIDER: The specified network provider name is invalid.")// ERROR_BAD_PROVIDER
        ERR(1205L, "ERROR_CANNOT_OPEN_PROFILE: Unable to open the network connection profile.")// ERROR_CANNOT_OPEN_PROFILE
        ERR(1206L, "ERROR_BAD_PROFILE: The network connection profile is corrupted.")// ERROR_BAD_PROFILE
        ERR(1207L, "ERROR_NOT_CONTAINER: Cannot enumerate a noncontainer.")// ERROR_NOT_CONTAINER
        ERR(1208L, "ERROR_EXTENDED_ERROR: An extended error has occurred.")// ERROR_EXTENDED_ERROR
        ERR(1209L, "ERROR_INVALID_GROUPNAME: The format of the specified group name is invalid.")// ERROR_INVALID_GROUPNAME
        ERR(1210L, "ERROR_INVALID_COMPUTERNAME: The format of the specified computer name is invalid.")// ERROR_INVALID_COMPUTERNAME
        ERR(1211L, "ERROR_INVALID_EVENTNAME: The format of the specified event name is invalid.")// ERROR_INVALID_EVENTNAME
        ERR(1212L, "ERROR_INVALID_DOMAINNAME: The format of the specified domain name is invalid.")// ERROR_INVALID_DOMAINNAME
        ERR(1213L, "ERROR_INVALID_SERVICENAME: The format of the specified service name is invalid.")// ERROR_INVALID_SERVICENAME
        ERR(1214L, "ERROR_INVALID_NETNAME: The format of the specified network name is invalid.")// ERROR_INVALID_NETNAME
        ERR(1215L, "ERROR_INVALID_SHARENAME: The format of the specified share name is invalid.")// ERROR_INVALID_SHARENAME
        ERR(1216L, "ERROR_INVALID_PASSWORDNAME: The format of the specified password is invalid.")// ERROR_INVALID_PASSWORDNAME
        ERR(1217L, "ERROR_INVALID_MESSAGENAME: The format of the specified message name is invalid.")// ERROR_INVALID_MESSAGENAME
        ERR(1218L, "ERROR_INVALID_MESSAGEDEST: The format of the specified message destination is invalid.")// ERROR_INVALID_MESSAGEDEST
        ERR(1219L, "ERROR_SESSION_CREDENTIAL_CONFLICT: The credentials supplied conflict with an existing set of credentials.")// ERROR_SESSION_CREDENTIAL_CONFLICT
        ERR(1220L, "ERROR_REMOTE_SESSION_LIMIT_EXCEEDED: An attempt was made to establish a session to a network server, but there are already too many sessions established to that server.")// ERROR_REMOTE_SESSION_LIMIT_EXCEEDED
        ERR(1221L, "ERROR_DUP_DOMAINNAME: The workgroup or domain name is already in use by another computer on the network.")// ERROR_DUP_DOMAINNAME
        ERR(1222L, "ERROR_NO_NETWORK: The network is not present or not started.")// ERROR_NO_NETWORK
        ERR(1223L, "ERROR_CANCELLED: The operation was canceled by the user.")// ERROR_CANCELLED
        ERR(1224L, "ERROR_USER_MAPPED_FILE: The requested operation cannot be performed on a file with a user-mapped section open.")// ERROR_USER_MAPPED_FILE
        ERR(1225L, "ERROR_CONNECTION_REFUSED: The remote system refused the network connection.")// ERROR_CONNECTION_REFUSED
        ERR(1226L, "ERROR_GRACEFUL_DISCONNECT: The network connection was gracefully closed.")// ERROR_GRACEFUL_DISCONNECT
        ERR(1227L, "ERROR_ADDRESS_ALREADY_ASSOCIATED: The network transport endpoint already has an address associated with it.")// ERROR_ADDRESS_ALREADY_ASSOCIATED
        ERR(1228L, "ERROR_ADDRESS_NOT_ASSOCIATED: An address has not yet been associated with the network endpoint.")// ERROR_ADDRESS_NOT_ASSOCIATED
        ERR(1229L, "ERROR_CONNECTION_INVALID: An operation was attempted on a nonexistent network connection.")// ERROR_CONNECTION_INVALID
        ERR(1230L, "ERROR_CONNECTION_ACTIVE: An invalid operation was attempted on an active network connection.")// ERROR_CONNECTION_ACTIVE
        ERR(1231L, "ERROR_NETWORK_UNREACHABLE: The network location cannot be reached. For information about network troubleshooting, see Windows Help.")// ERROR_NETWORK_UNREACHABLE
        ERR(1232L, "ERROR_HOST_UNREACHABLE: The network location cannot be reached. For information about network troubleshooting, see Windows Help.")// ERROR_HOST_UNREACHABLE
        ERR(1233L, "ERROR_PROTOCOL_UNREACHABLE: The network location cannot be reached. For information about network troubleshooting, see Windows Help.")// ERROR_PROTOCOL_UNREACHABLE
        ERR(1234L, "ERROR_PORT_UNREACHABLE: No service is operating at the destination network endpoint on the remote system.")// ERROR_PORT_UNREACHABLE
        ERR(1235L, "ERROR_REQUEST_ABORTED: The request was aborted.")// ERROR_REQUEST_ABORTED
        ERR(1236L, "ERROR_CONNECTION_ABORTED: The network connection was aborted by the local system.")// ERROR_CONNECTION_ABORTED
        ERR(1237L, "ERROR_RETRY: The operation could not be completed. A retry should be performed.")// ERROR_RETRY
        ERR(1238L, "ERROR_CONNECTION_COUNT_LIMIT: A connection to the server could not be made because the limit on the number of concurrent connections for this account has been reached.")// ERROR_CONNECTION_COUNT_LIMIT
        ERR(1239L, "ERROR_LOGIN_TIME_RESTRICTION: Attempting to log in during an unauthorized time of day for this account.")// ERROR_LOGIN_TIME_RESTRICTION
        ERR(1240L, "ERROR_LOGIN_WKSTA_RESTRICTION: The account is not authorized to log in from this station.")// ERROR_LOGIN_WKSTA_RESTRICTION
        ERR(1241L, "ERROR_INCORRECT_ADDRESS: The network address could not be used for the operation requested.")// ERROR_INCORRECT_ADDRESS
        ERR(1242L, "ERROR_ALREADY_REGISTERED: The service is already registered.")// ERROR_ALREADY_REGISTERED
        ERR(1243L, "ERROR_SERVICE_NOT_FOUND: The specified service does not exist.")// ERROR_SERVICE_NOT_FOUND
        ERR(1244L, "ERROR_NOT_AUTHENTICATED: The operation being requested was not performed because the user has not been authenticated.")// ERROR_NOT_AUTHENTICATED
        ERR(1245L, "ERROR_NOT_LOGGED_ON: The operation being requested was not performed because the user has not logged on to the network.")// ERROR_NOT_LOGGED_ON
        ERR(1246L , "ERROR_CONTINUE: Continue with work in progress.")// ERROR_CONTINUE
        ERR(1247L, "ERROR_ALREADY_INITIALIZED: An attempt was made to perform an initialization operation when initialization has already been completed.")// ERROR_ALREADY_INITIALIZED
        ERR(1248L , "ERROR_NO_MORE_DEVICES: No more local devices.")// ERROR_NO_MORE_DEVICES
        ERR(1249L, "ERROR_NO_SUCH_SITE: The specified site does not exist.")// ERROR_NO_SUCH_SITE
        ERR(1250L, "ERROR_DOMAIN_CONTROLLER_EXISTS: A domain controller with the specified name already exists.")// ERROR_DOMAIN_CONTROLLER_EXISTS
        ERR(1251L, "ERROR_ONLY_IF_CONNECTED: This operation is supported only when you are connected to the server.")// ERROR_ONLY_IF_CONNECTED
        ERR(1252L, "ERROR_OVERRIDE_NOCHANGES: The group policy framework should call the extension even if there are no changes.")// ERROR_OVERRIDE_NOCHANGES
        ERR(1253L, "ERROR_BAD_USER_PROFILE: The specified user does not have a valid profile.")// ERROR_BAD_USER_PROFILE
        ERR(1254L, "ERROR_NOT_SUPPORTED_ON_SBS: This operation is not supported on a Microsoft Small Business Server")// ERROR_NOT_SUPPORTED_ON_SBS
        ERR(1255L, "ERROR_SERVER_SHUTDOWN_IN_PROGRESS: The server machine is shutting down.")// ERROR_SERVER_SHUTDOWN_IN_PROGRESS
        ERR(1256L, "ERROR_HOST_DOWN: The remote system is not available. For information about network troubleshooting, see Windows Help.")// ERROR_HOST_DOWN
        ERR(1300L, "ERROR_NOT_ALL_ASSIGNED: Not all privileges referenced are assigned to the caller.")// ERROR_NOT_ALL_ASSIGNED
        ERR(1301L, "ERROR_SOME_NOT_MAPPED: Some mapping between account names and security IDs was not done.")// ERROR_SOME_NOT_MAPPED
        ERR(1302L, "ERROR_NO_QUOTAS_FOR_ACCOUNT: No system quota limits are specifically set for this account.")// ERROR_NO_QUOTAS_FOR_ACCOUNT
        ERR(1303L, "ERROR_LOCAL_USER_SESSION_KEY: No encryption key is available. A well-known encryption key was returned.")// ERROR_LOCAL_USER_SESSION_KEY
        ERR(1304L, "ERROR_NULL_LM_PASSWORD: The password is too complex to be converted to a LAN Manager password. The LAN Manager password returned is a NULL string.")// ERROR_NULL_LM_PASSWORD
        ERR(1305L, "ERROR_UNKNOWN_REVISION: The revision level is unknown.")// ERROR_UNKNOWN_REVISION
        ERR(1306L, "ERROR_REVISION_MISMATCH: Indicates two revision levels are incompatible.")// ERROR_REVISION_MISMATCH
        ERR(1307L, "ERROR_INVALID_OWNER: This security ID may not be assigned as the owner of this object.")// ERROR_INVALID_OWNER
        ERR(1308L, "ERROR_INVALID_PRIMARY_GROUP: This security ID may not be assigned as the primary group of an object.")// ERROR_INVALID_PRIMARY_GROUP
        ERR(1309L, "ERROR_NO_IMPERSONATION_TOKEN: An attempt has been made to operate on an impersonation token by a thread that is not currently impersonating a client.")// ERROR_NO_IMPERSONATION_TOKEN
        ERR(1310L, "ERROR_CANT_DISABLE_MANDATORY: The group may not be disabled.")// ERROR_CANT_DISABLE_MANDATORY
        ERR(1311L, "ERROR_NO_LOGON_SERVERS: There are currently no logon servers available to service the logon request.")// ERROR_NO_LOGON_SERVERS
        ERR(1312L, "ERROR_NO_SUCH_LOGON_SESSION: A specified logon session does not exist. It may already have been terminated.")// ERROR_NO_SUCH_LOGON_SESSION
        ERR(1313L, "ERROR_NO_SUCH_PRIVILEGE: A specified privilege does not exist.")// ERROR_NO_SUCH_PRIVILEGE
        ERR(1314L, "ERROR_PRIVILEGE_NOT_HELD: A required privilege is not held by the client.")// ERROR_PRIVILEGE_NOT_HELD
        ERR(1315L, "ERROR_INVALID_ACCOUNT_NAME: The name provided is not a properly formed account name.")// ERROR_INVALID_ACCOUNT_NAME
        ERR(1316L, "ERROR_USER_EXISTS: The specified user already exists.")// ERROR_USER_EXISTS
        ERR(1317L, "ERROR_NO_SUCH_USER: The specified user does not exist.")// ERROR_NO_SUCH_USER
        ERR(1318L, "ERROR_GROUP_EXISTS: The specified group already exists.")// ERROR_GROUP_EXISTS
        ERR(1319L, "ERROR_NO_SUCH_GROUP: The specified group does not exist.")// ERROR_NO_SUCH_GROUP
        ERR(1320L, "ERROR_MEMBER_IN_GROUP: Either the specified user account is already a member of the specified group, or the specified group cannot be deleted because it contains a member.")// ERROR_MEMBER_IN_GROUP
        ERR(1321L, "ERROR_MEMBER_NOT_IN_GROUP: The specified user account is not a member of the specified group account.")// ERROR_MEMBER_NOT_IN_GROUP
        ERR(1322L, "ERROR_LAST_ADMIN: The last remaining administration account cannot be disabled or deleted.")// ERROR_LAST_ADMIN
        ERR(1323L, "ERROR_WRONG_PASSWORD: Unable to update the password. The value provided as the current password is incorrect.")// ERROR_WRONG_PASSWORD
        ERR(1324L, "ERROR_ILL_FORMED_PASSWORD: Unable to update the password. The value provided for the new password contains values that are not allowed in passwords.")// ERROR_ILL_FORMED_PASSWORD
        ERR(1325L, "ERROR_PASSWORD_RESTRICTION: Unable to update the password. The value provided for the new password does not meet the length, complexity, or history requirement of the domain.")// ERROR_PASSWORD_RESTRICTION
        ERR(1326L, "ERROR_LOGON_FAILURE: Logon failure: unknown user name or bad password.")// ERROR_LOGON_FAILURE
        ERR(1327L, "ERROR_ACCOUNT_RESTRICTION: Logon failure: user account restriction.")// ERROR_ACCOUNT_RESTRICTION
        ERR(1328L, "ERROR_INVALID_LOGON_HOURS: Logon failure: account logon time restriction violation.")// ERROR_INVALID_LOGON_HOURS
        ERR(1329L, "ERROR_INVALID_WORKSTATION: Logon failure: user not allowed to log on to this computer.")// ERROR_INVALID_WORKSTATION
        ERR(1330L, "ERROR_PASSWORD_EXPIRED: Logon failure: the specified account password has expired.")// ERROR_PASSWORD_EXPIRED
        ERR(1331L, "ERROR_ACCOUNT_DISABLED: Logon failure: account currently disabled.")// ERROR_ACCOUNT_DISABLED
        ERR(1332L, "ERROR_NONE_MAPPED: No mapping between account names and security IDs was done.")// ERROR_NONE_MAPPED
        ERR(1333L, "ERROR_TOO_MANY_LUIDS_REQUESTED: Too many local user identifiers (LUIDs) were requested at one time.")// ERROR_TOO_MANY_LUIDS_REQUESTED
        ERR(1334L, "ERROR_LUIDS_EXHAUSTED: No more local user identifiers (LUIDs) are available.")// ERROR_LUIDS_EXHAUSTED
        ERR(1335L, "ERROR_INVALID_SUB_AUTHORITY: The subauthority part of a security ID is invalid for this particular use.")// ERROR_INVALID_SUB_AUTHORITY
        ERR(1336L, "ERROR_INVALID_ACL: The access control list (ACL) structure is invalid.")// ERROR_INVALID_ACL
        ERR(1337L, "ERROR_INVALID_SID: The security ID structure is invalid.")// ERROR_INVALID_SID
        ERR(1338L, "ERROR_INVALID_SECURITY_DESCR: The security descriptor structure is invalid.")// ERROR_INVALID_SECURITY_DESCR
        ERR(1340L, "ERROR_BAD_INHERITANCE_ACL: The inherited access control list (ACL) or access control entry (ACE) could not be built.")// ERROR_BAD_INHERITANCE_ACL
        ERR(1341L, "ERROR_SERVER_DISABLED: The server is currently disabled.")// ERROR_SERVER_DISABLED
        ERR(1342L, "ERROR_SERVER_NOT_DISABLED: The server is currently enabled.")// ERROR_SERVER_NOT_DISABLED
        ERR(1343L, "ERROR_INVALID_ID_AUTHORITY: The value provided was an invalid value for an identifier authority.")// ERROR_INVALID_ID_AUTHORITY
        ERR(1344L, "ERROR_ALLOTTED_SPACE_EXCEEDED: No more memory is available for security information updates.")// ERROR_ALLOTTED_SPACE_EXCEEDED
        ERR(1345L, "ERROR_INVALID_GROUP_ATTRIBUTES: The specified attributes are invalid, or incompatible with the attributes for the group as a whole.")// ERROR_INVALID_GROUP_ATTRIBUTES
        ERR(1346L, "ERROR_BAD_IMPERSONATION_LEVEL: Either a required impersonation level was not provided, or the provided impersonation level is invalid.")// ERROR_BAD_IMPERSONATION_LEVEL
        ERR(1347L, "ERROR_CANT_OPEN_ANONYMOUS: Cannot open an anonymous level security token.")// ERROR_CANT_OPEN_ANONYMOUS
        ERR(1348L, "ERROR_BAD_VALIDATION_CLASS: The validation information class requested was invalid.")// ERROR_BAD_VALIDATION_CLASS
        ERR(1349L, "ERROR_BAD_TOKEN_TYPE: The type of the token is inappropriate for its attempted use.")// ERROR_BAD_TOKEN_TYPE
        ERR(1350L, "ERROR_NO_SECURITY_ON_OBJECT: Unable to perform a security operation on an object that has no associated security.")// ERROR_NO_SECURITY_ON_OBJECT
        ERR(1351L, "ERROR_CANT_ACCESS_DOMAIN_INFO: Configuration information could not be read from the domain controller, either because the machine is unavailable, or access has been denied.")// ERROR_CANT_ACCESS_DOMAIN_INFO
        ERR(1352L, "ERROR_INVALID_SERVER_STATE: The security account manager (SAM) or local security authority (LSA) server was in the wrong state to perform the security operation.")// ERROR_INVALID_SERVER_STATE
        ERR(1353L, "ERROR_INVALID_DOMAIN_STATE: The domain was in the wrong state to perform the security operation.")// ERROR_INVALID_DOMAIN_STATE
        ERR(1354L, "ERROR_INVALID_DOMAIN_ROLE: This operation is only allowed for the Primary Domain Controller of the domain.")// ERROR_INVALID_DOMAIN_ROLE
        ERR(1355L, "ERROR_NO_SUCH_DOMAIN: The specified domain either does not exist or could not be contacted.")// ERROR_NO_SUCH_DOMAIN
        ERR(1356L, "ERROR_DOMAIN_EXISTS: The specified domain already exists.")// ERROR_DOMAIN_EXISTS
        ERR(1357L, "ERROR_DOMAIN_LIMIT_EXCEEDED: An attempt was made to exceed the limit on the number of domains per server.")// ERROR_DOMAIN_LIMIT_EXCEEDED
        ERR(1358L, "ERROR_INTERNAL_DB_CORRUPTION: Unable to complete the requested operation because of either a catastrophic media failure or a data structure corruption on the disk.")// ERROR_INTERNAL_DB_CORRUPTION
        ERR(1359L, "ERROR_INTERNAL_ERROR: An internal error occurred.")// ERROR_INTERNAL_ERROR
        ERR(1360L, "ERROR_GENERIC_NOT_MAPPED: Generic access types were contained in an access mask which should already be mapped to nongeneric types.")// ERROR_GENERIC_NOT_MAPPED
        ERR(1361L, "ERROR_BAD_DESCRIPTOR_FORMAT: A security descriptor is not in the right format (absolute or self-relative).")// ERROR_BAD_DESCRIPTOR_FORMAT
        ERR(1362L, "ERROR_NOT_LOGON_PROCESS: The requested action is restricted for use by logon processes only. The calling process has not registered as a logon process.")// ERROR_NOT_LOGON_PROCESS
        ERR(1363L, "ERROR_LOGON_SESSION_EXISTS: Cannot start a new logon session with an ID that is already in use.")// ERROR_LOGON_SESSION_EXISTS
        ERR(1364L, "ERROR_NO_SUCH_PACKAGE: A specified authentication package is unknown.")// ERROR_NO_SUCH_PACKAGE
        ERR(1365L, "ERROR_BAD_LOGON_SESSION_STATE: The logon session is not in a state that is consistent with the requested operation.")// ERROR_BAD_LOGON_SESSION_STATE
        ERR(1366L, "ERROR_LOGON_SESSION_COLLISION: The logon session ID is already in use.")// ERROR_LOGON_SESSION_COLLISION
        ERR(1367L, "ERROR_INVALID_LOGON_TYPE: A logon request contained an invalid logon type value.")// ERROR_INVALID_LOGON_TYPE
        ERR(1368L, "ERROR_CANNOT_IMPERSONATE: Unable to impersonate using a named pipe until data has been read from that pipe.")// ERROR_CANNOT_IMPERSONATE
        ERR(1369L, "ERROR_RXACT_INVALID_STATE: The transaction state of a registry subtree is incompatible with the requested operation.")// ERROR_RXACT_INVALID_STATE
        ERR(1370L, "ERROR_RXACT_COMMIT_FAILURE: An internal security database corruption has been encountered.")// ERROR_RXACT_COMMIT_FAILURE
        ERR(1371L, "ERROR_SPECIAL_ACCOUNT: Cannot perform this operation on built-in accounts.")// ERROR_SPECIAL_ACCOUNT
        ERR(1372L, "ERROR_SPECIAL_GROUP: Cannot perform this operation on this built-in special group.")// ERROR_SPECIAL_GROUP
        ERR(1373L, "ERROR_SPECIAL_USER: Cannot perform this operation on this built-in special user.")// ERROR_SPECIAL_USER
        ERR(1374L, "ERROR_MEMBERS_PRIMARY_GROUP: The user cannot be removed from a group because the group is currently the user's primary group.")// ERROR_MEMBERS_PRIMARY_GROUP
        ERR(1375L, "ERROR_TOKEN_ALREADY_IN_USE: The token is already in use as a primary token.")// ERROR_TOKEN_ALREADY_IN_USE
        ERR(1376L, "ERROR_NO_SUCH_ALIAS: The specified local group does not exist.")// ERROR_NO_SUCH_ALIAS
        ERR(1377L, "ERROR_MEMBER_NOT_IN_ALIAS: The specified account name is not a member of the local group.")// ERROR_MEMBER_NOT_IN_ALIAS
        ERR(1378L, "ERROR_MEMBER_IN_ALIAS: The specified account name is already a member of the local group.")// ERROR_MEMBER_IN_ALIAS
        ERR(1379L, "ERROR_ALIAS_EXISTS: The specified local group already exists.")// ERROR_ALIAS_EXISTS
        ERR(1380L, "ERROR_LOGON_NOT_GRANTED: Logon failure: the user has not been granted the requested logon type at this computer.")// ERROR_LOGON_NOT_GRANTED
        ERR(1381L, "ERROR_TOO_MANY_SECRETS: The maximum number of secrets that may be stored in a single system has been exceeded.")// ERROR_TOO_MANY_SECRETS
        ERR(1382L, "ERROR_SECRET_TOO_LONG: The length of a secret exceeds the maximum length allowed.")// ERROR_SECRET_TOO_LONG
        ERR(1383L, "ERROR_INTERNAL_DB_ERROR: The local security authority database contains an internal inconsistency.")// ERROR_INTERNAL_DB_ERROR
        ERR(1384L, "ERROR_TOO_MANY_CONTEXT_IDS: During a logon attempt, the user's security context accumulated too many security IDs.")// ERROR_TOO_MANY_CONTEXT_IDS
        ERR(1385L, "ERROR_LOGON_TYPE_NOT_GRANTED: Logon failure: the user has not been granted the requested logon type at this computer.")// ERROR_LOGON_TYPE_NOT_GRANTED
        ERR(1386L, "ERROR_NT_CROSS_ENCRYPTION_REQUIRED: A cross-encrypted password is necessary to change a user password.")// ERROR_NT_CROSS_ENCRYPTION_REQUIRED
        ERR(1387L, "ERROR_NO_SUCH_MEMBER: A member could not be added to or removed from the local group because the member does not exist.")// ERROR_NO_SUCH_MEMBER
        ERR(1388L, "ERROR_INVALID_MEMBER: A new member could not be added to a local group because the member has the wrong account type.")// ERROR_INVALID_MEMBER
        ERR(1389L, "ERROR_TOO_MANY_SIDS: Too many security IDs have been specified.")// ERROR_TOO_MANY_SIDS
        ERR(1390L, "ERROR_LM_CROSS_ENCRYPTION_REQUIRED: A cross-encrypted password is necessary to change this user password.")// ERROR_LM_CROSS_ENCRYPTION_REQUIRED
        ERR(1391L, "ERROR_NO_INHERITANCE: Indicates an ACL contains no inheritable components.")// ERROR_NO_INHERITANCE
        ERR(1392L, "ERROR_FILE_CORRUPT: The file or directory is corrupted and unreadable.")// ERROR_FILE_CORRUPT
        ERR(1393L, "ERROR_DISK_CORRUPT: The disk structure is corrupted and unreadable.")// ERROR_DISK_CORRUPT
        ERR(1394L, "ERROR_NO_USER_SESSION_KEY: There is no user session key for the specified logon session.")// ERROR_NO_USER_SESSION_KEY
        ERR(1395L, "ERROR_LICENSE_QUOTA_EXCEEDED: The service being accessed is licensed for a particular number of connections.")// ERROR_LICENSE_QUOTA_EXCEEDED
        ERR(1396L, "ERROR_WRONG_TARGET_NAME: Logon Failure: The target account name is incorrect.")// ERROR_WRONG_TARGET_NAME
        ERR(1397L, "ERROR_MUTUAL_AUTH_FAILED: Mutual Authentication failed. The server's password is out of date at the domain controller.")// ERROR_MUTUAL_AUTH_FAILED
        ERR(1398L, "ERROR_TIME_SKEW: There is a time difference between the client and server.")// ERROR_TIME_SKEW
        ERR(1399L, "ERROR_CURRENT_DOMAIN_NOT_ALLOWED: This operation can not be performed on the current domain.")// ERROR_CURRENT_DOMAIN_NOT_ALLOWED
        ERR(1400L, "ERROR_INVALID_WINDOW_HANDLE: Invalid window handle.")// ERROR_INVALID_WINDOW_HANDLE
        ERR(1401L, "ERROR_INVALID_MENU_HANDLE: Invalid menu handle.")// ERROR_INVALID_MENU_HANDLE
        ERR(1402L, "ERROR_INVALID_CURSOR_HANDLE: Invalid cursor handle.")// ERROR_INVALID_CURSOR_HANDLE
        ERR(1403L, "ERROR_INVALID_ACCEL_HANDLE: Invalid accelerator table handle.")// ERROR_INVALID_ACCEL_HANDLE
        ERR(1404L, "ERROR_INVALID_HOOK_HANDLE: Invalid hook handle.")// ERROR_INVALID_HOOK_HANDLE
        ERR(1405L, "ERROR_INVALID_DWP_HANDLE: Invalid handle to a multiple-window position structure.")// ERROR_INVALID_DWP_HANDLE
        ERR(1406L, "ERROR_TLW_WITH_WSCHILD: Cannot create a top-level child window.")// ERROR_TLW_WITH_WSCHILD
        ERR(1407L, "ERROR_CANNOT_FIND_WND_CLASS: Cannot find window class.")// ERROR_CANNOT_FIND_WND_CLASS
        ERR(1408L, "ERROR_WINDOW_OF_OTHER_THREAD: Invalid window; it belongs to other thread.")// ERROR_WINDOW_OF_OTHER_THREAD
        ERR(1409L, "ERROR_HOTKEY_ALREADY_REGISTERED: Hot key is already registered.")// ERROR_HOTKEY_ALREADY_REGISTERED
        ERR(1410L, "ERROR_CLASS_ALREADY_EXISTS: Class already exists.")// ERROR_CLASS_ALREADY_EXISTS
        ERR(1411L, "ERROR_CLASS_DOES_NOT_EXIST: Class does not exist.")// ERROR_CLASS_DOES_NOT_EXIST
        ERR(1412L, "ERROR_CLASS_HAS_WINDOWS: Class still has open windows.")// ERROR_CLASS_HAS_WINDOWS
        ERR(1413L, "ERROR_INVALID_INDEX: Invalid index.")// ERROR_INVALID_INDEX
        ERR(1414L, "ERROR_INVALID_ICON_HANDLE: Invalid icon handle.")// ERROR_INVALID_ICON_HANDLE
        ERR(1415L, "ERROR_PRIVATE_DIALOG_INDEX: Using private DIALOG window words.")// ERROR_PRIVATE_DIALOG_INDEX
        ERR(1416L, "ERROR_LISTBOX_ID_NOT_FOUND: The list box identifier was not found.")// ERROR_LISTBOX_ID_NOT_FOUND
        ERR(1417L, "ERROR_NO_WILDCARD_CHARACTERS: No wildcards were found.")// ERROR_NO_WILDCARD_CHARACTERS
        ERR(1418L, "ERROR_CLIPBOARD_NOT_OPEN: Thread does not have a clipboard open.")// ERROR_CLIPBOARD_NOT_OPEN
        ERR(1419L, "ERROR_HOTKEY_NOT_REGISTERED: Hot key is not registered.")// ERROR_HOTKEY_NOT_REGISTERED
        ERR(1420L, "ERROR_WINDOW_NOT_DIALOG: The window is not a valid dialog window.")// ERROR_WINDOW_NOT_DIALOG
        ERR(1421L, "ERROR_CONTROL_ID_NOT_FOUND: Control ID not found.")// ERROR_CONTROL_ID_NOT_FOUND
        ERR(1422L, "ERROR_INVALID_COMBOBOX_MESSAGE: Invalid message for a combo box because it does not have an edit control.")// ERROR_INVALID_COMBOBOX_MESSAGE
        ERR(1423L, "ERROR_WINDOW_NOT_COMBOBOX: The window is not a combo box.")// ERROR_WINDOW_NOT_COMBOBOX
        ERR(1424L, "ERROR_INVALID_EDIT_HEIGHT: Height must be less than 256.")// ERROR_INVALID_EDIT_HEIGHT
        ERR(1425L, "ERROR_DC_NOT_FOUND: Invalid device context (DC) handle.")// ERROR_DC_NOT_FOUND
        ERR(1426L, "ERROR_INVALID_HOOK_FILTER: Invalid hook procedure type.")// ERROR_INVALID_HOOK_FILTER
        ERR(1427L, "ERROR_INVALID_FILTER_PROC: Invalid hook procedure.")// ERROR_INVALID_FILTER_PROC
        ERR(1428L, "ERROR_HOOK_NEEDS_HMOD: Cannot set nonlocal hook without a module handle.")// ERROR_HOOK_NEEDS_HMOD
        ERR(1429L, "ERROR_GLOBAL_ONLY_HOOK: This hook procedure can only be set globally.")// ERROR_GLOBAL_ONLY_HOOK
        ERR(1430L, "ERROR_JOURNAL_HOOK_SET: The journal hook procedure is already installed.")// ERROR_JOURNAL_HOOK_SET
        ERR(1431L, "ERROR_HOOK_NOT_INSTALLED: The hook procedure is not installed.")// ERROR_HOOK_NOT_INSTALLED
        ERR(1432L, "ERROR_INVALID_LB_MESSAGE: Invalid message for single-selection list box.")// ERROR_INVALID_LB_MESSAGE
        ERR(1433L, "ERROR_SETCOUNT_ON_BAD_LB: LB_SETCOUNT sent to non-lazy list box.")// ERROR_SETCOUNT_ON_BAD_LB
        ERR(1434L, "ERROR_LB_WITHOUT_TABSTOPS: This list box does not support tab stops.")// ERROR_LB_WITHOUT_TABSTOPS
        ERR(1435L, "ERROR_DESTROY_OBJECT_OF_OTHER_THREAD: Cannot destroy object created by another thread.")// ERROR_DESTROY_OBJECT_OF_OTHER_THREAD
        ERR(1436L, "ERROR_CHILD_WINDOW_MENU: Child windows cannot have menus.")// ERROR_CHILD_WINDOW_MENU
        ERR(1437L, "ERROR_NO_SYSTEM_MENU: The window does not have a system menu.")// ERROR_NO_SYSTEM_MENU
        ERR(1438L, "ERROR_INVALID_MSGBOX_STYLE: Invalid message box style.")// ERROR_INVALID_MSGBOX_STYLE
        ERR(1439L, "ERROR_INVALID_SPI_VALUE: Invalid system-wide (SPI_*) parameter.")// ERROR_INVALID_SPI_VALUE
        ERR(1440L, "ERROR_SCREEN_ALREADY_LOCKED: Screen already locked.")// ERROR_SCREEN_ALREADY_LOCKED
        ERR(1441L, "ERROR_HWNDS_HAVE_DIFF_PARENT: All handles to windows in a multiple-window position structure must have the same parent.")// ERROR_HWNDS_HAVE_DIFF_PARENT
        ERR(1442L, "ERROR_NOT_CHILD_WINDOW: The window is not a child window.")// ERROR_NOT_CHILD_WINDOW
        ERR(1443L, "ERROR_INVALID_GW_COMMAND: Invalid GW_* command.")// ERROR_INVALID_GW_COMMAND
        ERR(1444L, "ERROR_INVALID_THREAD_ID: Invalid thread identifier.")// ERROR_INVALID_THREAD_ID
        ERR(1445L, "ERROR_NON_MDICHILD_WINDOW: Cannot process a message from a window that is not a multiple document interface (MDI) window.")// ERROR_NON_MDICHILD_WINDOW
        ERR(1446L, "ERROR_POPUP_ALREADY_ACTIVE: Popup menu already active.")// ERROR_POPUP_ALREADY_ACTIVE
        ERR(1447L, "ERROR_NO_SCROLLBARS: The window does not have scroll bars.")// ERROR_NO_SCROLLBARS
        ERR(1448L, "ERROR_INVALID_SCROLLBAR_RANGE: Scroll bar range cannot be greater than MAXLONG.")// ERROR_INVALID_SCROLLBAR_RANGE
        ERR(1449L, "ERROR_INVALID_SHOWWIN_COMMAND: Cannot show or remove the window in the way specified.")// ERROR_INVALID_SHOWWIN_COMMAND
        ERR(1450L, "ERROR_NO_SYSTEM_RESOURCES: Insufficient system resources exist to complete the requested service.")// ERROR_NO_SYSTEM_RESOURCES
        ERR(1451L, "ERROR_NONPAGED_SYSTEM_RESOURCES: Insufficient system resources exist to complete the requested service.")// ERROR_NONPAGED_SYSTEM_RESOURCES
        ERR(1452L, "ERROR_PAGED_SYSTEM_RESOURCES: Insufficient system resources exist to complete the requested service.")// ERROR_PAGED_SYSTEM_RESOURCES
        ERR(1453L, "ERROR_WORKING_SET_QUOTA: Insufficient quota to complete the requested service.")// ERROR_WORKING_SET_QUOTA
        ERR(1454L, "ERROR_PAGEFILE_QUOTA: Insufficient quota to complete the requested service.")// ERROR_PAGEFILE_QUOTA
        ERR(1455L, "ERROR_COMMITMENT_LIMIT: The paging file is too small for this operation to complete.")// ERROR_COMMITMENT_LIMIT
        ERR(1456L, "ERROR_MENU_ITEM_NOT_FOUND: A menu item was not found.")// ERROR_MENU_ITEM_NOT_FOUND
        ERR(1457L, "ERROR_INVALID_KEYBOARD_HANDLE: Invalid keyboard layout handle.")// ERROR_INVALID_KEYBOARD_HANDLE
        ERR(1458L, "ERROR_HOOK_TYPE_NOT_ALLOWED: Hook type not allowed.")// ERROR_HOOK_TYPE_NOT_ALLOWED
        ERR(1459L, "ERROR_REQUIRES_INTERACTIVE_WINDOWSTATION: This operation requires an interactive window station.")// ERROR_REQUIRES_INTERACTIVE_WINDOWSTATION
        ERR(1460L, "ERROR_TIMEOUT: This operation returned because the timeout period expired.")// ERROR_TIMEOUT
        ERR(1461L, "ERROR_INVALID_MONITOR_HANDLE: Invalid monitor handle.")// ERROR_INVALID_MONITOR_HANDLE
        ERR(1500L, "ERROR_EVENTLOG_FILE_CORRUPT: The event log file is corrupted.")// ERROR_EVENTLOG_FILE_CORRUPT
        ERR(1501L, "ERROR_EVENTLOG_CANT_START: No event log file could be opened, so the event logging service did not start.")// ERROR_EVENTLOG_CANT_START
        ERR(1502L, "ERROR_LOG_FILE_FULL: The event log file is full.")// ERROR_LOG_FILE_FULL
        ERR(1503L, "ERROR_EVENTLOG_FILE_CHANGED: The event log file has changed between read operations.")// ERROR_EVENTLOG_FILE_CHANGED
        ERR(1601L, "ERROR_INSTALL_SERVICE_FAILURE: The Windows Installer service could not be accessed. Contact your support personnel to verify that the Windows Installer service is properly registered.")// ERROR_INSTALL_SERVICE_FAILURE
        ERR(1602L, "ERROR_INSTALL_USEREXIT: User cancelled installation.")// ERROR_INSTALL_USEREXIT
        ERR(1603L, "ERROR_INSTALL_FAILURE: Fatal error during installation.")// ERROR_INSTALL_FAILURE
        ERR(1604L, "ERROR_INSTALL_SUSPEND: Installation suspended, incomplete.")// ERROR_INSTALL_SUSPEND
        ERR(1605L, "ERROR_UNKNOWN_PRODUCT: This action is only valid for products that are currently installed.")// ERROR_UNKNOWN_PRODUCT
        ERR(1606L, "ERROR_UNKNOWN_FEATURE: Feature ID not registered.")// ERROR_UNKNOWN_FEATURE
        ERR(1607L, "ERROR_UNKNOWN_COMPONENT: Component ID not registered.")// ERROR_UNKNOWN_COMPONENT
        ERR(1608L, "ERROR_UNKNOWN_PROPERTY: Unknown property.")// ERROR_UNKNOWN_PROPERTY
        ERR(1609L, "ERROR_INVALID_HANDLE_STATE: Handle is in an invalid state.")// ERROR_INVALID_HANDLE_STATE
        ERR(1610L, "ERROR_BAD_CONFIGURATION: The configuration data for this product is corrupt. Contact your support personnel.")// ERROR_BAD_CONFIGURATION
        ERR(1611L, "ERROR_INDEX_ABSENT: Component qualifier not present.")// ERROR_INDEX_ABSENT
        ERR(1612L, "ERROR_INSTALL_SOURCE_ABSENT: The installation source for this product is not available. Verify that the source exists and that you can access it.")// ERROR_INSTALL_SOURCE_ABSENT
        ERR(1613L, "ERROR_INSTALL_PACKAGE_VERSION: This installation package cannot be installed by the Windows Installer service. You must install a Windows service pack that contains a newer version of the Windows Installer service.")// ERROR_INSTALL_PACKAGE_VERSION
        ERR(1614L, "ERROR_PRODUCT_UNINSTALLED: Product is uninstalled.")// ERROR_PRODUCT_UNINSTALLED
        ERR(1615L, "ERROR_BAD_QUERY_SYNTAX: SQL query syntax invalid or unsupported.")// ERROR_BAD_QUERY_SYNTAX
        ERR(1616L, "ERROR_INVALID_FIELD: Record field does not exist.")// ERROR_INVALID_FIELD
        ERR(1617L, "ERROR_DEVICE_REMOVED: The device has been removed.")// ERROR_DEVICE_REMOVED
        ERR(1618L, "ERROR_INSTALL_ALREADY_RUNNING: Another installation is already in progress. Complete that installation before proceeding with this install.")// ERROR_INSTALL_ALREADY_RUNNING
        ERR(1619L, "ERROR_INSTALL_PACKAGE_OPEN_FAILED: This installation package could not be opened. Verify that the package exists and that you can access it, or contact the application vendor to verify that this is a valid Windows Installer package.")// ERROR_INSTALL_PACKAGE_OPEN_FAILED
        ERR(1620L, "ERROR_INSTALL_PACKAGE_INVALID: This installation package could not be opened. Contact the application vendor to verify that this is a valid Windows Installer package.")// ERROR_INSTALL_PACKAGE_INVALID
        ERR(1621L, "ERROR_INSTALL_UI_FAILURE: There was an error starting the Windows Installer service user interface. Contact your support personnel.")// ERROR_INSTALL_UI_FAILURE
        ERR(1622L, "ERROR_INSTALL_LOG_FAILURE: Error opening installation log file. Verify that the specified log file location exists and that you can write to it.")// ERROR_INSTALL_LOG_FAILURE
        ERR(1623L, "ERROR_INSTALL_LANGUAGE_UNSUPPORTED: The language of this installation package is not supported by your system.")// ERROR_INSTALL_LANGUAGE_UNSUPPORTED
        ERR(1624L, "ERROR_INSTALL_TRANSFORM_FAILURE: Error applying transforms. Verify that the specified transform paths are valid.")// ERROR_INSTALL_TRANSFORM_FAILURE
        ERR(1625L, "ERROR_INSTALL_PACKAGE_REJECTED: This installation is forbidden by system policy. Contact your system administrator.")// ERROR_INSTALL_PACKAGE_REJECTED
        ERR(1626L, "ERROR_FUNCTION_NOT_CALLED: Function could not be executed.")// ERROR_FUNCTION_NOT_CALLED
        ERR(1627L, "ERROR_FUNCTION_FAILED: Function failed during execution.")// ERROR_FUNCTION_FAILED
        ERR(1628L, "ERROR_INVALID_TABLE: Invalid or unknown table specified.")// ERROR_INVALID_TABLE
        ERR(1629L, "ERROR_DATATYPE_MISMATCH: Data supplied is of wrong type.")// ERROR_DATATYPE_MISMATCH
        ERR(1630L, "ERROR_UNSUPPORTED_TYPE: Data of this type is not supported.")// ERROR_UNSUPPORTED_TYPE
        ERR(1631L, "ERROR_CREATE_FAILED: The Windows Installer service failed to start. Contact your support personnel.")// ERROR_CREATE_FAILED
        ERR(1632L, "ERROR_INSTALL_TEMP_UNWRITABLE: The temp folder is either full or inaccessible. Verify that the temp folder exists and that you can write to it.")// ERROR_INSTALL_TEMP_UNWRITABLE
        ERR(1633L, "ERROR_INSTALL_PLATFORM_UNSUPPORTED: This installation package is not supported by this processor type. Contact your product vendor.")// ERROR_INSTALL_PLATFORM_UNSUPPORTED
        ERR(1634L, "ERROR_INSTALL_NOTUSED: Component not used on this computer.")// ERROR_INSTALL_NOTUSED
        ERR(1635L, "ERROR_PATCH_PACKAGE_OPEN_FAILED: This patch package could not be opened. Verify that the patch package exists and that you can access it, or contact the application vendor to verify that this is a valid Windows Installer patch package.")// ERROR_PATCH_PACKAGE_OPEN_FAILED
        ERR(1636L, "ERROR_PATCH_PACKAGE_INVALID: This patch package could not be opened. Contact the application vendor to verify that this is a valid Windows Installer patch package.")// ERROR_PATCH_PACKAGE_INVALID
        ERR(1637L, "ERROR_PATCH_PACKAGE_UNSUPPORTED: This patch package cannot be processed by the Windows Installer service. You must install a Windows service pack that contains a newer version of the Windows Installer service.")// ERROR_PATCH_PACKAGE_UNSUPPORTED
        ERR(1638L, "ERROR_PRODUCT_VERSION: Another version of this product is already installed. Installation of this version cannot continue. To configure or remove the existing version of this product, use Add/Remove Programs on the Control Panel.")// ERROR_PRODUCT_VERSION
        ERR(1639L, "ERROR_INVALID_COMMAND_LINE: Invalid command line argument. Consult the Windows Installer SDK for detailed command line help.")// ERROR_INVALID_COMMAND_LINE
        ERR(1640L, "ERROR_INSTALL_REMOTE_DISALLOWED: Only administrators have permission to add, remove, or configure server software during a Terminal services remote session. If you want to install or configure software on the server, contact your network administrator.")// ERROR_INSTALL_REMOTE_DISALLOWED
        ERR(1641L, "ERROR_SUCCESS_REBOOT_INITIATED: The requested operation completed successfully. The system will be restarted so the changes can take effect.")// ERROR_SUCCESS_REBOOT_INITIATED
        ERR(1642L, "ERROR_PATCH_TARGET_NOT_FOUND: The upgrade patch cannot be installed by the Windows Installer service because the program to be upgraded may be missing, or the upgrade patch may update a different version of the program. Verify that the program to be upgraded exists on your computer and that you have the correct upgrade patch.")// ERROR_PATCH_TARGET_NOT_FOUND
        ERR(1643L, "ERROR_PATCH_PACKAGE_REJECTED: The patch package is not permitted by system policy. It is not signed with an appropriate certificate.")// ERROR_PATCH_PACKAGE_REJECTED
        ERR(1644L, "ERROR_INSTALL_TRANSFORM_REJECTED: One or more customizations are not permitted by system policy. They are not signed with an appropriate certificate.")// ERROR_INSTALL_TRANSFORM_REJECTED
        ERR(1700L, "RPC_S_INVALID_STRING_BINDING: The string binding is invalid.")// RPC_S_INVALID_STRING_BINDING
        ERR(1701L, "RPC_S_WRONG_KIND_OF_BINDING: The binding handle is not the correct type.")// RPC_S_WRONG_KIND_OF_BINDING
        ERR(1702L, "RPC_S_INVALID_BINDING: The binding handle is invalid.")// RPC_S_INVALID_BINDING
        ERR(1703L, "RPC_S_PROTSEQ_NOT_SUPPORTED: The RPC protocol sequence is not supported.")// RPC_S_PROTSEQ_NOT_SUPPORTED
        ERR(1704L, "RPC_S_INVALID_RPC_PROTSEQ: The RPC protocol sequence is invalid.")// RPC_S_INVALID_RPC_PROTSEQ
        ERR(1705L, "RPC_S_INVALID_STRING_UUID: The string universal unique identifier (UUID) is invalid.")// RPC_S_INVALID_STRING_UUID
        ERR(1706L, "RPC_S_INVALID_ENDPOINT_FORMAT: The endpoint format is invalid.")// RPC_S_INVALID_ENDPOINT_FORMAT
        ERR(1707L, "RPC_S_INVALID_NET_ADDR: The network address is invalid.")// RPC_S_INVALID_NET_ADDR
        ERR(1708L, "RPC_S_NO_ENDPOINT_FOUND: No endpoint was found.")// RPC_S_NO_ENDPOINT_FOUND
        ERR(1709L, "RPC_S_INVALID_TIMEOUT: The timeout value is invalid.")// RPC_S_INVALID_TIMEOUT
        ERR(1710L, "RPC_S_OBJECT_NOT_FOUND: The object universal unique identifier (UUID) was not found.")// RPC_S_OBJECT_NOT_FOUND
        ERR(1711L, "RPC_S_ALREADY_REGISTERED: The object universal unique identifier (UUID) has already been registered.")// RPC_S_ALREADY_REGISTERED
        ERR(1712L, "RPC_S_TYPE_ALREADY_REGISTERED: The type universal unique identifier (UUID) has already been registered.")// RPC_S_TYPE_ALREADY_REGISTERED
        ERR(1713L, "RPC_S_ALREADY_LISTENING: The RPC server is already listening.")// RPC_S_ALREADY_LISTENING
        ERR(1714L, "RPC_S_NO_PROTSEQS_REGISTERED: No protocol sequences have been registered.")// RPC_S_NO_PROTSEQS_REGISTERED
        ERR(1715L, "RPC_S_NOT_LISTENING: The RPC server is not listening.")// RPC_S_NOT_LISTENING
        ERR(1716L, "RPC_S_UNKNOWN_MGR_TYPE: The manager type is unknown.")// RPC_S_UNKNOWN_MGR_TYPE
        ERR(1717L, "RPC_S_UNKNOWN_IF: The interface is unknown.")// RPC_S_UNKNOWN_IF
        ERR(1718L, "RPC_S_NO_BINDINGS: There are no bindings.")// RPC_S_NO_BINDINGS
        ERR(1719L, "RPC_S_NO_PROTSEQS: There are no protocol sequences.")// RPC_S_NO_PROTSEQS
        ERR(1720L, "RPC_S_CANT_CREATE_ENDPOINT: The endpoint cannot be created.")// RPC_S_CANT_CREATE_ENDPOINT
        ERR(1721L, "RPC_S_OUT_OF_RESOURCES: Not enough resources are available to complete this operation.")// RPC_S_OUT_OF_RESOURCES
        ERR(1722L, "RPC_S_SERVER_UNAVAILABLE: The RPC server is unavailable.")// RPC_S_SERVER_UNAVAILABLE
        ERR(1723L, "RPC_S_SERVER_TOO_BUSY: The RPC server is too busy to complete this operation.")// RPC_S_SERVER_TOO_BUSY
        ERR(1724L, "RPC_S_INVALID_NETWORK_OPTIONS: The network options are invalid.")// RPC_S_INVALID_NETWORK_OPTIONS
        ERR(1725L, "RPC_S_NO_CALL_ACTIVE: There are no remote procedure calls active on this thread.")// RPC_S_NO_CALL_ACTIVE
        ERR(1726L, "RPC_S_CALL_FAILED: The remote procedure call failed.")// RPC_S_CALL_FAILED
        ERR(1727L, "RPC_S_CALL_FAILED_DNE: The remote procedure call failed and did not execute.")// RPC_S_CALL_FAILED_DNE
        ERR(1728L, "RPC_S_PROTOCOL_ERROR: A remote procedure call (RPC) protocol error occurred.")// RPC_S_PROTOCOL_ERROR
        ERR(1730L, "RPC_S_UNSUPPORTED_TRANS_SYN: The transfer syntax is not supported by the RPC server.")// RPC_S_UNSUPPORTED_TRANS_SYN
        ERR(1732L, "RPC_S_UNSUPPORTED_TYPE: The universal unique identifier (UUID) type is not supported.")// RPC_S_UNSUPPORTED_TYPE
        ERR(1733L, "RPC_S_INVALID_TAG: The tag is invalid.")// RPC_S_INVALID_TAG
        ERR(1734L, "RPC_S_INVALID_BOUND: The array bounds are invalid.")// RPC_S_INVALID_BOUND
        ERR(1735L, "RPC_S_NO_ENTRY_NAME: The binding does not contain an entry name.")// RPC_S_NO_ENTRY_NAME
        ERR(1736L, "RPC_S_INVALID_NAME_SYNTAX: The name syntax is invalid.")// RPC_S_INVALID_NAME_SYNTAX
        ERR(1737L, "RPC_S_UNSUPPORTED_NAME_SYNTAX: The name syntax is not supported.")// RPC_S_UNSUPPORTED_NAME_SYNTAX
        ERR(1739L, "RPC_S_UUID_NO_ADDRESS: No network address is available to use to construct a universal unique identifier (UUID).")// RPC_S_UUID_NO_ADDRESS
        ERR(1740L, "RPC_S_DUPLICATE_ENDPOINT: The endpoint is a duplicate.")// RPC_S_DUPLICATE_ENDPOINT
        ERR(1741L, "RPC_S_UNKNOWN_AUTHN_TYPE: The authentication type is unknown.")// RPC_S_UNKNOWN_AUTHN_TYPE
        ERR(1742L, "RPC_S_MAX_CALLS_TOO_SMALL: The maximum number of calls is too small.")// RPC_S_MAX_CALLS_TOO_SMALL
        ERR(1743L, "RPC_S_STRING_TOO_LONG: The string is too long.")// RPC_S_STRING_TOO_LONG
        ERR(1744L, "RPC_S_PROTSEQ_NOT_FOUND: The RPC protocol sequence was not found.")// RPC_S_PROTSEQ_NOT_FOUND
        ERR(1745L, "RPC_S_PROCNUM_OUT_OF_RANGE: The procedure number is out of range.")// RPC_S_PROCNUM_OUT_OF_RANGE
        ERR(1746L, "RPC_S_BINDING_HAS_NO_AUTH: The binding does not contain any authentication information.")// RPC_S_BINDING_HAS_NO_AUTH
        ERR(1747L, "RPC_S_UNKNOWN_AUTHN_SERVICE: The authentication service is unknown.")// RPC_S_UNKNOWN_AUTHN_SERVICE
        ERR(1748L, "RPC_S_UNKNOWN_AUTHN_LEVEL: The authentication level is unknown.")// RPC_S_UNKNOWN_AUTHN_LEVEL
        ERR(1749L, "RPC_S_INVALID_AUTH_IDENTITY: The security context is invalid.")// RPC_S_INVALID_AUTH_IDENTITY
        ERR(1750L, "RPC_S_UNKNOWN_AUTHZ_SERVICE: The authorization service is unknown.")// RPC_S_UNKNOWN_AUTHZ_SERVICE
        ERR(1751L, "EPT_S_INVALID_ENTRY: The entry is invalid.")// EPT_S_INVALID_ENTRY
        ERR(1752L, "EPT_S_CANT_PERFORM_OP: The server endpoint cannot perform the operation.")// EPT_S_CANT_PERFORM_OP
        ERR(1753L, "EPT_S_NOT_REGISTERED: There are no more endpoints available from the endpoint mapper.")// EPT_S_NOT_REGISTERED
        ERR(1754L, "RPC_S_NOTHING_TO_EXPORT: No interfaces have been exported.")// RPC_S_NOTHING_TO_EXPORT
        ERR(1755L, "RPC_S_INCOMPLETE_NAME: The entry name is incomplete.")// RPC_S_INCOMPLETE_NAME
        ERR(1756L, "RPC_S_INVALID_VERS_OPTION: The version option is invalid.")// RPC_S_INVALID_VERS_OPTION
        ERR(1757L, "RPC_S_NO_MORE_MEMBERS: There are no more members.")// RPC_S_NO_MORE_MEMBERS
        ERR(1758L, "RPC_S_NOT_ALL_OBJS_UNEXPORTED: There is nothing to unexport.")// RPC_S_NOT_ALL_OBJS_UNEXPORTED
        ERR(1759L, "RPC_S_INTERFACE_NOT_FOUND: The interface was not found.")// RPC_S_INTERFACE_NOT_FOUND
        ERR(1760L, "RPC_S_ENTRY_ALREADY_EXISTS: The entry already exists.")// RPC_S_ENTRY_ALREADY_EXISTS
        ERR(1761L, "RPC_S_ENTRY_NOT_FOUND: The entry is not found.")// RPC_S_ENTRY_NOT_FOUND
        ERR(1762L, "RPC_S_NAME_SERVICE_UNAVAILABLE: The name service is unavailable.")// RPC_S_NAME_SERVICE_UNAVAILABLE
        ERR(1763L, "RPC_S_INVALID_NAF_ID: The network address family is invalid.")// RPC_S_INVALID_NAF_ID
        ERR(1764L, "RPC_S_CANNOT_SUPPORT: The requested operation is not supported.")// RPC_S_CANNOT_SUPPORT
        ERR(1765L, "RPC_S_NO_CONTEXT_AVAILABLE: No security context is available to allow impersonation.")// RPC_S_NO_CONTEXT_AVAILABLE
        ERR(1766L, "RPC_S_INTERNAL_ERROR: An internal error occurred in a remote procedure call (RPC).")// RPC_S_INTERNAL_ERROR
        ERR(1767L, "RPC_S_ZERO_DIVIDE: The RPC server attempted an integer division by zero.")// RPC_S_ZERO_DIVIDE
        ERR(1768L, "RPC_S_ADDRESS_ERROR: An addressing error occurred in the RPC server.")// RPC_S_ADDRESS_ERROR
        ERR(1769L, "RPC_S_FP_DIV_ZERO: A floating-point operation at the RPC server caused a division by zero.")// RPC_S_FP_DIV_ZERO
        ERR(1770L, "RPC_S_FP_UNDERFLOW: A floating-point underflow occurred at the RPC server.")// RPC_S_FP_UNDERFLOW
        ERR(1771L, "RPC_S_FP_OVERFLOW: A floating-point overflow occurred at the RPC server.")// RPC_S_FP_OVERFLOW
        ERR(1772L, "RPC_X_NO_MORE_ENTRIES: The list of RPC servers available for the binding of auto handles has been exhausted.")// RPC_X_NO_MORE_ENTRIES
        ERR(1773L, "RPC_X_SS_CHAR_TRANS_OPEN_FAIL: Unable to open the character translation table file.")// RPC_X_SS_CHAR_TRANS_OPEN_FAIL
        ERR(1774L, "RPC_X_SS_CHAR_TRANS_SHORT_FILE: The file containing the character translation table has fewer than 512 bytes.")// RPC_X_SS_CHAR_TRANS_SHORT_FILE
        ERR(1775L, "RPC_X_SS_IN_NULL_CONTEXT: A null context handle was passed from the client to the host during a remote procedure call.")// RPC_X_SS_IN_NULL_CONTEXT
        ERR(1777L, "RPC_X_SS_CONTEXT_DAMAGED: The context handle changed during a remote procedure call.")// RPC_X_SS_CONTEXT_DAMAGED
        ERR(1778L, "RPC_X_SS_HANDLES_MISMATCH: The binding handles passed to a remote procedure call do not match.")// RPC_X_SS_HANDLES_MISMATCH
        ERR(1779L, "RPC_X_SS_CANNOT_GET_CALL_HANDLE: The stub is unable to get the remote procedure call handle.")// RPC_X_SS_CANNOT_GET_CALL_HANDLE
        ERR(1780L, "RPC_X_NULL_REF_POINTER: A null reference pointer was passed to the stub.")// RPC_X_NULL_REF_POINTER
        ERR(1781L, "RPC_X_ENUM_VALUE_OUT_OF_RANGE: The enumeration value is out of range.")// RPC_X_ENUM_VALUE_OUT_OF_RANGE
        ERR(1782L, "RPC_X_BYTE_COUNT_TOO_SMALL: The byte count is too small.")// RPC_X_BYTE_COUNT_TOO_SMALL
        ERR(1783L, "RPC_X_BAD_STUB_DATA: The stub received bad data.")// RPC_X_BAD_STUB_DATA
        ERR(1784L, "ERROR_INVALID_USER_BUFFER: The supplied user buffer is not valid for the requested operation.")// ERROR_INVALID_USER_BUFFER
        ERR(1785L, "ERROR_UNRECOGNIZED_MEDIA: The disk media is not recognized. It may not be formatted.")// ERROR_UNRECOGNIZED_MEDIA
        ERR(1786L, "ERROR_NO_TRUST_LSA_SECRET: The workstation does not have a trust secret.")// ERROR_NO_TRUST_LSA_SECRET
        ERR(1787L, "ERROR_NO_TRUST_SAM_ACCOUNT: The security database on the server does not have a computer account for this workstation trust relationship.")// ERROR_NO_TRUST_SAM_ACCOUNT
        ERR(1788L, "ERROR_TRUSTED_DOMAIN_FAILURE: The trust relationship between the primary domain and the trusted domain failed.")// ERROR_TRUSTED_DOMAIN_FAILURE
        ERR(1789L, "ERROR_TRUSTED_RELATIONSHIP_FAILURE: The trust relationship between this workstation and the primary domain failed.")// ERROR_TRUSTED_RELATIONSHIP_FAILURE
        ERR(1790L, "ERROR_TRUST_FAILURE: The network logon failed.")// ERROR_TRUST_FAILURE
        ERR(1791L, "RPC_S_CALL_IN_PROGRESS: A remote procedure call is already in progress for this thread.")// RPC_S_CALL_IN_PROGRESS
        ERR(1792L, "ERROR_NETLOGON_NOT_STARTED: An attempt was made to logon, but the network logon service was not started.")// ERROR_NETLOGON_NOT_STARTED
        ERR(1793L, "ERROR_ACCOUNT_EXPIRED: The user's account has expired.")// ERROR_ACCOUNT_EXPIRED
        ERR(1794L, "ERROR_REDIRECTOR_HAS_OPEN_HANDLES: The redirector is in use and cannot be unloaded.")// ERROR_REDIRECTOR_HAS_OPEN_HANDLES
        ERR(1795L, "ERROR_PRINTER_DRIVER_ALREADY_INSTALLED: The specified printer driver is already installed.")// ERROR_PRINTER_DRIVER_ALREADY_INSTALLED
        ERR(1796L, "ERROR_UNKNOWN_PORT: The specified port is unknown.")// ERROR_UNKNOWN_PORT
        ERR(1797L, "ERROR_UNKNOWN_PRINTER_DRIVER: The printer driver is unknown.")// ERROR_UNKNOWN_PRINTER_DRIVER
        ERR(1798L, "ERROR_UNKNOWN_PRINTPROCESSOR: The print processor is unknown.")// ERROR_UNKNOWN_PRINTPROCESSOR
        ERR(1799L, "ERROR_INVALID_SEPARATOR_FILE: The specified separator file is invalid.")// ERROR_INVALID_SEPARATOR_FILE
        ERR(1800L, "ERROR_INVALID_PRIORITY: The specified priority is invalid.")// ERROR_INVALID_PRIORITY
        ERR(1801L, "ERROR_INVALID_PRINTER_NAME: The printer name is invalid.")// ERROR_INVALID_PRINTER_NAME
        ERR(1802L, "ERROR_PRINTER_ALREADY_EXISTS: The printer already exists.")// ERROR_PRINTER_ALREADY_EXISTS
        ERR(1803L, "ERROR_INVALID_PRINTER_COMMAND: The printer command is invalid.")// ERROR_INVALID_PRINTER_COMMAND
        ERR(1804L, "ERROR_INVALID_DATATYPE: The specified datatype is invalid.")// ERROR_INVALID_DATATYPE
        ERR(1805L, "ERROR_INVALID_ENVIRONMENT: The environment specified is invalid.")// ERROR_INVALID_ENVIRONMENT
        ERR(1806L, "RPC_S_NO_MORE_BINDINGS: There are no more bindings.")// RPC_S_NO_MORE_BINDINGS
        ERR(1807L, "ERROR_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT: The account used is an interdomain trust account. Use your global user account or local user account to access this server.")// ERROR_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT
        ERR(1808L, "ERROR_NOLOGON_WORKSTATION_TRUST_ACCOUNT: The account used is a computer account. Use your global user account or local user account to access this server.")// ERROR_NOLOGON_WORKSTATION_TRUST_ACCOUNT
        ERR(1809L, "ERROR_NOLOGON_SERVER_TRUST_ACCOUNT: The account used is a server trust account. Use your global user account or local user account to access this server.")// ERROR_NOLOGON_SERVER_TRUST_ACCOUNT
        ERR(1810L, "ERROR_DOMAIN_TRUST_INCONSISTENT: The name or security ID (SID) of the domain specified is inconsistent with the trust information for that domain.")// ERROR_DOMAIN_TRUST_INCONSISTENT
        ERR(1811L, "ERROR_SERVER_HAS_OPEN_HANDLES: The server is in use and cannot be unloaded.")// ERROR_SERVER_HAS_OPEN_HANDLES
        ERR(1812L, "ERROR_RESOURCE_DATA_NOT_FOUND: The specified image file did not contain a resource section.")// ERROR_RESOURCE_DATA_NOT_FOUND
        ERR(1813L, "ERROR_RESOURCE_TYPE_NOT_FOUND: The specified resource type cannot be found in the image file.")// ERROR_RESOURCE_TYPE_NOT_FOUND
        ERR(1814L, "ERROR_RESOURCE_NAME_NOT_FOUND: The specified resource name cannot be found in the image file.")// ERROR_RESOURCE_NAME_NOT_FOUND
        ERR(1815L, "ERROR_RESOURCE_LANG_NOT_FOUND: The specified resource language ID cannot be found in the image file.")// ERROR_RESOURCE_LANG_NOT_FOUND
        ERR(1816L, "ERROR_NOT_ENOUGH_QUOTA: Not enough quota is available to process this command.")// ERROR_NOT_ENOUGH_QUOTA
        ERR(1817L, "RPC_S_NO_INTERFACES: No interfaces have been registered.")// RPC_S_NO_INTERFACES
        ERR(1818L, "RPC_S_CALL_CANCELLED: The remote procedure call was cancelled.")// RPC_S_CALL_CANCELLED
        ERR(1819L, "RPC_S_BINDING_INCOMPLETE: The binding handle does not contain all required information.")// RPC_S_BINDING_INCOMPLETE
        ERR(1820L, "RPC_S_COMM_FAILURE: A communications failure occurred during a remote procedure call.")// RPC_S_COMM_FAILURE
        ERR(1821L, "RPC_S_UNSUPPORTED_AUTHN_LEVEL: The requested authentication level is not supported.")// RPC_S_UNSUPPORTED_AUTHN_LEVEL
        ERR(1822L, "RPC_S_NO_PRINC_NAME: No principal name registered.")// RPC_S_NO_PRINC_NAME
        ERR(1823L, "RPC_S_NOT_RPC_ERROR: The error specified is not a valid Windows RPC error code.")// RPC_S_NOT_RPC_ERROR
        ERR(1824L, "RPC_S_UUID_LOCAL_ONLY: A UUID that is valid only on this computer has been allocated.")// RPC_S_UUID_LOCAL_ONLY
        ERR(1825L, "RPC_S_SEC_PKG_ERROR: A security package specific error occurred.")// RPC_S_SEC_PKG_ERROR
        ERR(1826L, "RPC_S_NOT_CANCELLED: Thread is not canceled.")// RPC_S_NOT_CANCELLED
        ERR(1827L, "RPC_X_INVALID_ES_ACTION: Invalid operation on the encoding/decoding handle.")// RPC_X_INVALID_ES_ACTION
        ERR(1828L, "RPC_X_WRONG_ES_VERSION: Incompatible version of the serializing package.")// RPC_X_WRONG_ES_VERSION
        ERR(1829L, "RPC_X_WRONG_STUB_VERSION: Incompatible version of the RPC stub.")// RPC_X_WRONG_STUB_VERSION
        ERR(1830L, "RPC_X_INVALID_PIPE_OBJECT: The RPC pipe object is invalid or corrupted.")// RPC_X_INVALID_PIPE_OBJECT
        ERR(1831L, "RPC_X_WRONG_PIPE_ORDER: An invalid operation was attempted on an RPC pipe object.")// RPC_X_WRONG_PIPE_ORDER
        ERR(1832L, "RPC_X_WRONG_PIPE_VERSION: Unsupported RPC pipe version.")// RPC_X_WRONG_PIPE_VERSION
        ERR(1898L, "RPC_S_GROUP_MEMBER_NOT_FOUND: The group member was not found.")// RPC_S_GROUP_MEMBER_NOT_FOUND
        ERR(1899L, "EPT_S_CANT_CREATE: The endpoint mapper database entry could not be created.")// EPT_S_CANT_CREATE
        ERR(1900L, "RPC_S_INVALID_OBJECT: The object universal unique identifier (UUID) is the nil UUID.")// RPC_S_INVALID_OBJECT
        ERR(1901L, "ERROR_INVALID_TIME: The specified time is invalid.")// ERROR_INVALID_TIME
        ERR(1902L, "ERROR_INVALID_FORM_NAME: The specified form name is invalid.")// ERROR_INVALID_FORM_NAME
        ERR(1903L, "ERROR_INVALID_FORM_SIZE: The specified form size is invalid.")// ERROR_INVALID_FORM_SIZE
        ERR(1904L, "ERROR_ALREADY_WAITING: The specified printer handle is already being waited on")// ERROR_ALREADY_WAITING
        ERR(1905L, "ERROR_PRINTER_DELETED: The specified printer has been deleted.")// ERROR_PRINTER_DELETED
        ERR(1906L, "ERROR_INVALID_PRINTER_STATE: The state of the printer is invalid.")// ERROR_INVALID_PRINTER_STATE
        ERR(1907L, "ERROR_PASSWORD_MUST_CHANGE: The user's password must be changed before logging on the first time.")// ERROR_PASSWORD_MUST_CHANGE
        ERR(1908L, "ERROR_DOMAIN_CONTROLLER_NOT_FOUND: Could not find the domain controller for this domain.")// ERROR_DOMAIN_CONTROLLER_NOT_FOUND
        ERR(1909L, "ERROR_ACCOUNT_LOCKED_OUT: The referenced account is currently locked out and may not be logged on to.")// ERROR_ACCOUNT_LOCKED_OUT
        ERR(1910L, "OR_INVALID_OXID: The object exporter specified was not found.")// OR_INVALID_OXID
        ERR(1911L, "OR_INVALID_OID: The object specified was not found.")// OR_INVALID_OID
        ERR(1912L, "OR_INVALID_SET: The object resolver set specified was not found.")// OR_INVALID_SET
        ERR(1913L, "RPC_S_SEND_INCOMPLETE: Some data remains to be sent in the request buffer.")// RPC_S_SEND_INCOMPLETE
        ERR(1914L, "RPC_S_INVALID_ASYNC_HANDLE: Invalid asynchronous remote procedure call handle.")// RPC_S_INVALID_ASYNC_HANDLE
        ERR(1915L, "RPC_S_INVALID_ASYNC_CALL: Invalid asynchronous RPC call handle for this operation.")// RPC_S_INVALID_ASYNC_CALL
        ERR(1916L, "RPC_X_PIPE_CLOSED: The RPC pipe object has already been closed.")// RPC_X_PIPE_CLOSED
        ERR(1917L, "RPC_X_PIPE_DISCIPLINE_ERROR: The RPC call completed before all pipes were processed.")// RPC_X_PIPE_DISCIPLINE_ERROR
        ERR(1918L, "RPC_X_PIPE_EMPTY: No more data is available from the RPC pipe.")// RPC_X_PIPE_EMPTY
        ERR(1919L, "ERROR_NO_SITENAME: No site name is available for this machine.")// ERROR_NO_SITENAME
        ERR(1920L, "ERROR_CANT_ACCESS_FILE: The file can not be accessed by the system.")// ERROR_CANT_ACCESS_FILE
        ERR(1921L, "ERROR_CANT_RESOLVE_FILENAME: The name of the file cannot be resolved by the system.")// ERROR_CANT_RESOLVE_FILENAME
        ERR(1922L, "RPC_S_ENTRY_TYPE_MISMATCH: The entry is not of the expected type.")// RPC_S_ENTRY_TYPE_MISMATCH
        ERR(1923L, "RPC_S_NOT_ALL_OBJS_EXPORTED: Not all object UUIDs could be exported to the specified entry.")// RPC_S_NOT_ALL_OBJS_EXPORTED
        ERR(1924L, "RPC_S_INTERFACE_NOT_EXPORTED: Interface could not be exported to the specified entry.")// RPC_S_INTERFACE_NOT_EXPORTED
        ERR(1925L, "RPC_S_PROFILE_NOT_ADDED: The specified profile entry could not be added.")// RPC_S_PROFILE_NOT_ADDED
        ERR(1926L, "RPC_S_PRF_ELT_NOT_ADDED: The specified profile element could not be added.")// RPC_S_PRF_ELT_NOT_ADDED
        ERR(1927L, "RPC_S_PRF_ELT_NOT_REMOVED: The specified profile element could not be removed.")// RPC_S_PRF_ELT_NOT_REMOVED
        ERR(1928L, "RPC_S_GRP_ELT_NOT_ADDED: The group element could not be added.")// RPC_S_GRP_ELT_NOT_ADDED
        ERR(1929L, "RPC_S_GRP_ELT_NOT_REMOVED: The group element could not be removed.")// RPC_S_GRP_ELT_NOT_REMOVED
        ERR(6118L, "ERROR_NO_BROWSER_SERVERS_FOUND: The list of servers for this workgroup is not currently available")// ERROR_NO_BROWSER_SERVERS_FOUND
        ERR(2000L, "ERROR_INVALID_PIXEL_FORMAT: The pixel format is invalid.")// ERROR_INVALID_PIXEL_FORMAT
        ERR(2001L, "ERROR_BAD_DRIVER: The specified driver is invalid.")// ERROR_BAD_DRIVER
        ERR(2002L, "ERROR_INVALID_WINDOW_STYLE: The window style or class attribute is invalid for this operation.")// ERROR_INVALID_WINDOW_STYLE
        ERR(2003L, "ERROR_METAFILE_NOT_SUPPORTED: The requested metafile operation is not supported.")// ERROR_METAFILE_NOT_SUPPORTED
        ERR(2004L, "ERROR_TRANSFORM_NOT_SUPPORTED: The requested transformation operation is not supported.")// ERROR_TRANSFORM_NOT_SUPPORTED
        ERR(2005L, "ERROR_CLIPPING_NOT_SUPPORTED: The requested clipping operation is not supported.")// ERROR_CLIPPING_NOT_SUPPORTED
        ERR(2010L, "ERROR_INVALID_CMM: The specified color management module is invalid.")// ERROR_INVALID_CMM
        ERR(2011L, "ERROR_INVALID_PROFILE: The specified color profile is invalid.")// ERROR_INVALID_PROFILE
        ERR(2012L, "ERROR_TAG_NOT_FOUND: The specified tag was not found.")// ERROR_TAG_NOT_FOUND
        ERR(2013L, "ERROR_TAG_NOT_PRESENT: A required tag is not present.")// ERROR_TAG_NOT_PRESENT
        ERR(2014L, "ERROR_DUPLICATE_TAG: The specified tag is already present.")// ERROR_DUPLICATE_TAG
        ERR(2015L, "ERROR_PROFILE_NOT_ASSOCIATED_WITH_DEVICE: The specified color profile is not associated with any device.")// ERROR_PROFILE_NOT_ASSOCIATED_WITH_DEVICE
        ERR(2016L, "ERROR_PROFILE_NOT_FOUND: The specified color profile was not found.")// ERROR_PROFILE_NOT_FOUND
        ERR(2017L, "ERROR_INVALID_COLORSPACE: The specified color space is invalid.")// ERROR_INVALID_COLORSPACE
        ERR(2018L, "ERROR_ICM_NOT_ENABLED: Image Color Management is not enabled.")// ERROR_ICM_NOT_ENABLED
        ERR(2019L, "ERROR_DELETING_ICM_XFORM: There was an error while deleting the color transform.")// ERROR_DELETING_ICM_XFORM
        ERR(2020L, "ERROR_INVALID_TRANSFORM: The specified color transform is invalid.")// ERROR_INVALID_TRANSFORM
        ERR(2021L, "ERROR_COLORSPACE_MISMATCH: The specified transform does not match the bitmap's color space.")// ERROR_COLORSPACE_MISMATCH
        ERR(2022L, "ERROR_INVALID_COLORINDEX: The specified named color index is not present in the profile.")// ERROR_INVALID_COLORINDEX
        ERR(2108L, "ERROR_CONNECTED_OTHER_PASSWORD: The network connection was made successfully, but the user had to be prompted for a password other than the one originally specified.")// ERROR_CONNECTED_OTHER_PASSWORD
        ERR(2202L, "ERROR_BAD_USERNAME: The specified username is invalid.")// ERROR_BAD_USERNAME
        ERR(2250L, "ERROR_NOT_CONNECTED: This network connection does not exist.")// ERROR_NOT_CONNECTED
        ERR(2401L, "ERROR_OPEN_FILES: This network connection has files open or requests pending.")// ERROR_OPEN_FILES
        ERR(2402L, "ERROR_ACTIVE_CONNECTIONS: Active connections still exist.")// ERROR_ACTIVE_CONNECTIONS
        ERR(2404L, "ERROR_DEVICE_IN_USE: The device is in use by an active process and cannot be disconnected.")// ERROR_DEVICE_IN_USE
        ERR(3000L, "ERROR_UNKNOWN_PRINT_MONITOR: The specified print monitor is unknown.")// ERROR_UNKNOWN_PRINT_MONITOR
        ERR(3001L, "ERROR_PRINTER_DRIVER_IN_USE: The specified printer driver is currently in use.")// ERROR_PRINTER_DRIVER_IN_USE
        ERR(3002L, "ERROR_SPOOL_FILE_NOT_FOUND: The spool file was not found.")// ERROR_SPOOL_FILE_NOT_FOUND
        ERR(3003L, "ERROR_SPL_NO_STARTDOC: A StartDocPrinter call was not issued.")// ERROR_SPL_NO_STARTDOC
        ERR(3004L, "ERROR_SPL_NO_ADDJOB: An AddJob call was not issued.")// ERROR_SPL_NO_ADDJOB
        ERR(3005L, "ERROR_PRINT_PROCESSOR_ALREADY_INSTALLED: The specified print processor has already been installed.")// ERROR_PRINT_PROCESSOR_ALREADY_INSTALLED
        ERR(3006L, "ERROR_PRINT_MONITOR_ALREADY_INSTALLED: The specified print monitor has already been installed.")// ERROR_PRINT_MONITOR_ALREADY_INSTALLED
        ERR(3007L, "ERROR_INVALID_PRINT_MONITOR: The specified print monitor does not have the required functions.")// ERROR_INVALID_PRINT_MONITOR
        ERR(3008L, "ERROR_PRINT_MONITOR_IN_USE: The specified print monitor is currently in use.")// ERROR_PRINT_MONITOR_IN_USE
        ERR(3009L, "ERROR_PRINTER_HAS_JOBS_QUEUED: The requested operation is not allowed when there are jobs queued to the printer.")// ERROR_PRINTER_HAS_JOBS_QUEUED
        ERR(3010L, "ERROR_SUCCESS_REBOOT_REQUIRED: The requested operation is successful. Changes will not be effective until the system is rebooted.")// ERROR_SUCCESS_REBOOT_REQUIRED
        ERR(3011L, "ERROR_SUCCESS_RESTART_REQUIRED: The requested operation is successful. Changes will not be effective until the service is restarted.")// ERROR_SUCCESS_RESTART_REQUIRED
        ERR(3012L, "ERROR_PRINTER_NOT_FOUND: No printers were found.")// ERROR_PRINTER_NOT_FOUND
        ERR(4000L, "ERROR_WINS_INTERNAL: WINS encountered an error while processing the command.")// ERROR_WINS_INTERNAL
        ERR(4001L, "ERROR_CAN_NOT_DEL_LOCAL_WINS: The local WINS can not be deleted.")// ERROR_CAN_NOT_DEL_LOCAL_WINS
        ERR(4002L, "ERROR_STATIC_INIT: The importation from the file failed.")// ERROR_STATIC_INIT
        ERR(4003L, "ERROR_INC_BACKUP: The backup failed. Was a full backup done before?")// ERROR_INC_BACKUP
        ERR(4004L, "ERROR_FULL_BACKUP: The backup failed. Check the directory to which you are backing the database.")// ERROR_FULL_BACKUP
        ERR(4005L, "ERROR_REC_NON_EXISTENT: The name does not exist in the WINS database.")// ERROR_REC_NON_EXISTENT
        ERR(4006L, "ERROR_RPL_NOT_ALLOWED: Replication with a nonconfigured partner is not allowed.")// ERROR_RPL_NOT_ALLOWED
        ERR(4100L, "ERROR_DHCP_ADDRESS_CONFLICT: The DHCP client has obtained an IP address that is already in use on the network. The local interface will be disabled until the DHCP client can obtain a new address.")// ERROR_DHCP_ADDRESS_CONFLICT
        ERR(4200L, "ERROR_WMI_GUID_NOT_FOUND: The GUID passed was not recognized as valid by a WMI data provider.")// ERROR_WMI_GUID_NOT_FOUND
        ERR(4201L, "ERROR_WMI_INSTANCE_NOT_FOUND: The instance name passed was not recognized as valid by a WMI data provider.")// ERROR_WMI_INSTANCE_NOT_FOUND
        ERR(4202L, "ERROR_WMI_ITEMID_NOT_FOUND: The data item ID passed was not recognized as valid by a WMI data provider.")// ERROR_WMI_ITEMID_NOT_FOUND
        ERR(4203L, "ERROR_WMI_TRY_AGAIN: The WMI request could not be completed and should be retried.")// ERROR_WMI_TRY_AGAIN
        ERR(4204L, "ERROR_WMI_DP_NOT_FOUND: The WMI data provider could not be located.")// ERROR_WMI_DP_NOT_FOUND
        ERR(4205L, "ERROR_WMI_UNRESOLVED_INSTANCE_REF: The WMI data provider references an instance set that has not been registered.")// ERROR_WMI_UNRESOLVED_INSTANCE_REF
        ERR(4206L, "ERROR_WMI_ALREADY_ENABLED: The WMI data block or event notification has already been enabled.")// ERROR_WMI_ALREADY_ENABLED
        ERR(4207L, "ERROR_WMI_GUID_DISCONNECTED: The WMI data block is no longer available.")// ERROR_WMI_GUID_DISCONNECTED
        ERR(4208L, "ERROR_WMI_SERVER_UNAVAILABLE: The WMI data service is not available.")// ERROR_WMI_SERVER_UNAVAILABLE
        ERR(4209L, "ERROR_WMI_DP_FAILED: The WMI data provider failed to carry out the request.")// ERROR_WMI_DP_FAILED
        ERR(4210L, "ERROR_WMI_INVALID_MOF: The WMI MOF information is not valid.")// ERROR_WMI_INVALID_MOF
        ERR(4211L, "ERROR_WMI_INVALID_REGINFO: The WMI registration information is not valid.")// ERROR_WMI_INVALID_REGINFO
        ERR(4212L, "ERROR_WMI_ALREADY_DISABLED: The WMI data block or event notification has already been disabled.")// ERROR_WMI_ALREADY_DISABLED
        ERR(4213L, "ERROR_WMI_READ_ONLY: The WMI data item or data block is read only.")// ERROR_WMI_READ_ONLY
        ERR(4214L, "ERROR_WMI_SET_FAILURE: The WMI data item or data block could not be changed.")// ERROR_WMI_SET_FAILURE
        ERR(4300L, "ERROR_INVALID_MEDIA: The media identifier does not represent a valid medium.")// ERROR_INVALID_MEDIA
        ERR(4301L, "ERROR_INVALID_LIBRARY: The library identifier does not represent a valid library.")// ERROR_INVALID_LIBRARY
        ERR(4302L, "ERROR_INVALID_MEDIA_POOL: The media pool identifier does not represent a valid media pool.")// ERROR_INVALID_MEDIA_POOL
        ERR(4303L, "ERROR_DRIVE_MEDIA_MISMATCH: The drive and medium are not compatible or exist in different libraries.")// ERROR_DRIVE_MEDIA_MISMATCH
        ERR(4304L, "ERROR_MEDIA_OFFLINE: The medium currently exists in an offline library and must be online to perform this operation.")// ERROR_MEDIA_OFFLINE
        ERR(4305L, "ERROR_LIBRARY_OFFLINE: The operation cannot be performed on an offline library.")// ERROR_LIBRARY_OFFLINE
        ERR(4306L, "ERROR_EMPTY: The library, drive, or media pool is empty.")// ERROR_EMPTY
        ERR(4307L, "ERROR_NOT_EMPTY: The library, drive, or media pool must be empty to perform this operation.")// ERROR_NOT_EMPTY
        ERR(4308L, "ERROR_MEDIA_UNAVAILABLE: No media is currently available in this media pool or library.")// ERROR_MEDIA_UNAVAILABLE
        ERR(4309L, "ERROR_RESOURCE_DISABLED: A resource required for this operation is disabled.")// ERROR_RESOURCE_DISABLED
        ERR(4310L, "ERROR_INVALID_CLEANER: The media identifier does not represent a valid cleaner.")// ERROR_INVALID_CLEANER
        ERR(4311L, "ERROR_UNABLE_TO_CLEAN: The drive cannot be cleaned or does not support cleaning.")// ERROR_UNABLE_TO_CLEAN
        ERR(4312L, "ERROR_OBJECT_NOT_FOUND: The object identifier does not represent a valid object.")// ERROR_OBJECT_NOT_FOUND
        ERR(4313L, "ERROR_DATABASE_FAILURE: Unable to read from or write to the database.")// ERROR_DATABASE_FAILURE
        ERR(4314L, "ERROR_DATABASE_FULL: The database is full.")// ERROR_DATABASE_FULL
        ERR(4315L, "ERROR_MEDIA_INCOMPATIBLE: The medium is not compatible with the device or media pool.")// ERROR_MEDIA_INCOMPATIBLE
        ERR(4316L, "ERROR_RESOURCE_NOT_PRESENT: The resource required for this operation does not exist.")// ERROR_RESOURCE_NOT_PRESENT
        ERR(4317L, "ERROR_INVALID_OPERATION: The operation identifier is not valid.")// ERROR_INVALID_OPERATION
        ERR(4318L, "ERROR_MEDIA_NOT_AVAILABLE: The media is not mounted or ready for use.")// ERROR_MEDIA_NOT_AVAILABLE
        ERR(4319L, "ERROR_DEVICE_NOT_AVAILABLE: The device is not ready for use.")// ERROR_DEVICE_NOT_AVAILABLE
        ERR(4320L, "ERROR_REQUEST_REFUSED: The operator or administrator has refused the request.")// ERROR_REQUEST_REFUSED
        ERR(4321L, "ERROR_INVALID_DRIVE_OBJECT: The drive identifier does not represent a valid drive.")// ERROR_INVALID_DRIVE_OBJECT
        ERR(4322L, "ERROR_LIBRARY_FULL: Library is full. No slot is available for use.")// ERROR_LIBRARY_FULL
        ERR(4323L, "ERROR_MEDIUM_NOT_ACCESSIBLE: The transport cannot access the medium.")// ERROR_MEDIUM_NOT_ACCESSIBLE
        ERR(4324L, "ERROR_UNABLE_TO_LOAD_MEDIUM: Unable to load the medium into the drive.")// ERROR_UNABLE_TO_LOAD_MEDIUM
        ERR(4325L, "ERROR_UNABLE_TO_INVENTORY_DRIVE: Unable to retrieve the drive status.")// ERROR_UNABLE_TO_INVENTORY_DRIVE
        ERR(4326L, "ERROR_UNABLE_TO_INVENTORY_SLOT: Unable to retrieve the slot status.")// ERROR_UNABLE_TO_INVENTORY_SLOT
        ERR(4327L, "ERROR_UNABLE_TO_INVENTORY_TRANSPORT: Unable to retrieve status about the transport.")// ERROR_UNABLE_TO_INVENTORY_TRANSPORT
        ERR(4328L, "ERROR_TRANSPORT_FULL: Cannot use the transport because it is already in use.")// ERROR_TRANSPORT_FULL
        ERR(4329L, "ERROR_CONTROLLING_IEPORT: Unable to open or close the inject/eject port.")// ERROR_CONTROLLING_IEPORT
        ERR(4330L, "ERROR_UNABLE_TO_EJECT_MOUNTED_MEDIA: Unable to eject the medium because it is in a drive.")// ERROR_UNABLE_TO_EJECT_MOUNTED_MEDIA
        ERR(4331L, "ERROR_CLEANER_SLOT_SET: A cleaner slot is already reserved.")// ERROR_CLEANER_SLOT_SET
        ERR(4332L, "ERROR_CLEANER_SLOT_NOT_SET: A cleaner slot is not reserved.")// ERROR_CLEANER_SLOT_NOT_SET
        ERR(4333L, "ERROR_CLEANER_CARTRIDGE_SPENT: The cleaner cartridge has performed the maximum number of drive cleanings.")// ERROR_CLEANER_CARTRIDGE_SPENT
        ERR(4334L, "ERROR_UNEXPECTED_OMID: Unexpected on-medium identifier.")// ERROR_UNEXPECTED_OMID
        ERR(4335L, "ERROR_CANT_DELETE_LAST_ITEM: The last remaining item in this group or resource cannot be deleted.")// ERROR_CANT_DELETE_LAST_ITEM
        ERR(4336L, "ERROR_MESSAGE_EXCEEDS_MAX_SIZE: The message provided exceeds the maximum size allowed for this parameter.")// ERROR_MESSAGE_EXCEEDS_MAX_SIZE
        ERR(4337L, "ERROR_VOLUME_CONTAINS_SYS_FILES: The volume contains system or paging files.")// ERROR_VOLUME_CONTAINS_SYS_FILES
        ERR(4338L, "ERROR_INDIGENOUS_TYPE: The media type cannot be removed from this library since at least one drive in the library reports it can support this media type.")// ERROR_INDIGENOUS_TYPE
        ERR(4339L, "ERROR_NO_SUPPORTING_DRIVES: This offline media cannot be mounted on this system since no enabled drives are present which can be used.")// ERROR_NO_SUPPORTING_DRIVES
        ERR(4350L, "ERROR_FILE_OFFLINE: The remote storage service was not able to recall the file.")// ERROR_FILE_OFFLINE
        ERR(4351L, "ERROR_REMOTE_STORAGE_NOT_ACTIVE: The remote storage service is not operational at this time.")// ERROR_REMOTE_STORAGE_NOT_ACTIVE
        ERR(4352L, "ERROR_REMOTE_STORAGE_MEDIA_ERROR: The remote storage service encountered a media error.")// ERROR_REMOTE_STORAGE_MEDIA_ERROR
        ERR(4390L, "ERROR_NOT_A_REPARSE_POINT: The file or directory is not a reparse point.")// ERROR_NOT_A_REPARSE_POINT
        ERR(4391L, "ERROR_REPARSE_ATTRIBUTE_CONFLICT: The reparse point attribute cannot be set because it conflicts with an existing attribute.")// ERROR_REPARSE_ATTRIBUTE_CONFLICT
        ERR(4392L, "ERROR_INVALID_REPARSE_DATA: The data present in the reparse point buffer is invalid.")// ERROR_INVALID_REPARSE_DATA
        ERR(4393L, "ERROR_REPARSE_TAG_INVALID: The tag present in the reparse point buffer is invalid.")// ERROR_REPARSE_TAG_INVALID
        ERR(4394L, "ERROR_REPARSE_TAG_MISMATCH: There is a mismatch between the tag specified in the request and the tag present in the reparse point.")// ERROR_REPARSE_TAG_MISMATCH
        ERR(4500L, "ERROR_VOLUME_NOT_SIS_ENABLED: Single Instance Storage is not available on this volume.")// ERROR_VOLUME_NOT_SIS_ENABLED
        ERR(5001L, "ERROR_DEPENDENT_RESOURCE_EXISTS: The cluster resource cannot be moved to another group because other resources are dependent on it.")// ERROR_DEPENDENT_RESOURCE_EXISTS
        ERR(5002L, "ERROR_DEPENDENCY_NOT_FOUND: The cluster resource dependency cannot be found.")// ERROR_DEPENDENCY_NOT_FOUND
        ERR(5003L, "ERROR_DEPENDENCY_ALREADY_EXISTS: The cluster resource cannot be made dependent on the specified resource because it is already dependent.")// ERROR_DEPENDENCY_ALREADY_EXISTS
        ERR(5004L, "ERROR_RESOURCE_NOT_ONLINE: The cluster resource is not online.")// ERROR_RESOURCE_NOT_ONLINE
        ERR(5005L, "ERROR_HOST_NODE_NOT_AVAILABLE: A cluster node is not available for this operation.")// ERROR_HOST_NODE_NOT_AVAILABLE
        ERR(5006L, "ERROR_RESOURCE_NOT_AVAILABLE: The cluster resource is not available.")// ERROR_RESOURCE_NOT_AVAILABLE
        ERR(5007L, "ERROR_RESOURCE_NOT_FOUND: The cluster resource could not be found.")// ERROR_RESOURCE_NOT_FOUND
        ERR(5008L, "ERROR_SHUTDOWN_CLUSTER: The cluster is being shut down.")// ERROR_SHUTDOWN_CLUSTER
        ERR(5009L, "ERROR_CANT_EVICT_ACTIVE_NODE: A cluster node cannot be evicted from the cluster unless the node is down.")// ERROR_CANT_EVICT_ACTIVE_NODE
        ERR(5010L, "ERROR_OBJECT_ALREADY_EXISTS: The object already exists.")// ERROR_OBJECT_ALREADY_EXISTS
        ERR(5011L, "ERROR_OBJECT_IN_LIST: The object is already in the list.")// ERROR_OBJECT_IN_LIST
        ERR(5012L, "ERROR_GROUP_NOT_AVAILABLE: The cluster group is not available for any new requests.")// ERROR_GROUP_NOT_AVAILABLE
        ERR(5013L, "ERROR_GROUP_NOT_FOUND: The cluster group could not be found.")// ERROR_GROUP_NOT_FOUND
        ERR(5014L, "ERROR_GROUP_NOT_ONLINE: The operation could not be completed because the cluster group is not online.")// ERROR_GROUP_NOT_ONLINE
        ERR(5015L, "ERROR_HOST_NODE_NOT_RESOURCE_OWNER: The cluster node is not the owner of the resource.")// ERROR_HOST_NODE_NOT_RESOURCE_OWNER
        ERR(5016L, "ERROR_HOST_NODE_NOT_GROUP_OWNER: The cluster node is not the owner of the group.")// ERROR_HOST_NODE_NOT_GROUP_OWNER
        ERR(5017L, "ERROR_RESMON_CREATE_FAILED: The cluster resource could not be created in the specified resource monitor.")// ERROR_RESMON_CREATE_FAILED
        ERR(5018L, "ERROR_RESMON_ONLINE_FAILED: The cluster resource could not be brought online by the resource monitor.")// ERROR_RESMON_ONLINE_FAILED
        ERR(5019L, "ERROR_RESOURCE_ONLINE: The operation could not be completed because the cluster resource is online.")// ERROR_RESOURCE_ONLINE
        ERR(5020L, "ERROR_QUORUM_RESOURCE: The cluster resource could not be deleted or brought offline because it is the quorum resource.")// ERROR_QUORUM_RESOURCE
        ERR(5021L, "ERROR_NOT_QUORUM_CAPABLE: The cluster could not make the specified resource a quorum resource because it is not capable of being a quorum resource.")// ERROR_NOT_QUORUM_CAPABLE
        ERR(5022L, "ERROR_CLUSTER_SHUTTING_DOWN: The cluster software is shutting down.")// ERROR_CLUSTER_SHUTTING_DOWN
        ERR(5023L, "ERROR_INVALID_STATE: The group or resource is not in the correct state to perform the requested operation.")// ERROR_INVALID_STATE
        ERR(5024L, "ERROR_RESOURCE_PROPERTIES_STORED: The properties were stored but not all changes will take effect until the next time the resource is brought online.")// ERROR_RESOURCE_PROPERTIES_STORED
        ERR(5025L, "ERROR_NOT_QUORUM_CLASS: The cluster could not make the specified resource a quorum resource because it does not belong to a shared storage class.")// ERROR_NOT_QUORUM_CLASS
        ERR(5026L, "ERROR_CORE_RESOURCE: The cluster resource could not be deleted since it is a core resource.")// ERROR_CORE_RESOURCE
        ERR(5027L, "ERROR_QUORUM_RESOURCE_ONLINE_FAILED: The quorum resource failed to come online.")// ERROR_QUORUM_RESOURCE_ONLINE_FAILED
        ERR(5028L, "ERROR_QUORUMLOG_OPEN_FAILED: The quorum log could not be created or mounted successfully.")// ERROR_QUORUMLOG_OPEN_FAILED
        ERR(5029L, "ERROR_CLUSTERLOG_CORRUPT: The cluster log is corrupt.")// ERROR_CLUSTERLOG_CORRUPT
        ERR(5030L, "ERROR_CLUSTERLOG_RECORD_EXCEEDS_MAXSIZE: The record could not be written to the cluster log since it exceeds the maximum size.")// ERROR_CLUSTERLOG_RECORD_EXCEEDS_MAXSIZE
        ERR(5031L, "ERROR_CLUSTERLOG_EXCEEDS_MAXSIZE: The cluster log exceeds its maximum size.")// ERROR_CLUSTERLOG_EXCEEDS_MAXSIZE
        ERR(5032L, "ERROR_CLUSTERLOG_CHKPOINT_NOT_FOUND: No checkpoint record was found in the cluster log.")// ERROR_CLUSTERLOG_CHKPOINT_NOT_FOUND
        ERR(5033L, "ERROR_CLUSTERLOG_NOT_ENOUGH_SPACE: The minimum required disk space needed for logging is not available.")// ERROR_CLUSTERLOG_NOT_ENOUGH_SPACE
        ERR(5034L, "ERROR_QUORUM_OWNER_ALIVE: The cluster node failed to take control of the quorum resource because the resource is owned by another active node.")// ERROR_QUORUM_OWNER_ALIVE
        ERR(5035L, "ERROR_NETWORK_NOT_AVAILABLE: A cluster network is not available for this operation.")// ERROR_NETWORK_NOT_AVAILABLE
        ERR(5036L, "ERROR_NODE_NOT_AVAILABLE: A cluster node is not available for this operation.")// ERROR_NODE_NOT_AVAILABLE
        ERR(5037L, "ERROR_ALL_NODES_NOT_AVAILABLE: All cluster nodes must be running to perform this operation.")// ERROR_ALL_NODES_NOT_AVAILABLE
        ERR(5038L, "ERROR_RESOURCE_FAILED: A cluster resource failed.")// ERROR_RESOURCE_FAILED
        ERR(5039L, "ERROR_CLUSTER_INVALID_NODE: The cluster node is not valid.")// ERROR_CLUSTER_INVALID_NODE
        ERR(5040L, "ERROR_CLUSTER_NODE_EXISTS: The cluster node already exists.")// ERROR_CLUSTER_NODE_EXISTS
        ERR(5041L, "ERROR_CLUSTER_JOIN_IN_PROGRESS: A node is in the process of joining the cluster.")// ERROR_CLUSTER_JOIN_IN_PROGRESS
        ERR(5042L, "ERROR_CLUSTER_NODE_NOT_FOUND: The cluster node was not found.")// ERROR_CLUSTER_NODE_NOT_FOUND
        ERR(5043L, "ERROR_CLUSTER_LOCAL_NODE_NOT_FOUND: The cluster local node information was not found.")// ERROR_CLUSTER_LOCAL_NODE_NOT_FOUND
        ERR(5044L, "ERROR_CLUSTER_NETWORK_EXISTS: The cluster network already exists.")// ERROR_CLUSTER_NETWORK_EXISTS
        ERR(5045L, "ERROR_CLUSTER_NETWORK_NOT_FOUND: The cluster network was not found.")// ERROR_CLUSTER_NETWORK_NOT_FOUND
        ERR(5046L, "ERROR_CLUSTER_NETINTERFACE_EXISTS: The cluster network interface already exists.")// ERROR_CLUSTER_NETINTERFACE_EXISTS
        ERR(5047L, "ERROR_CLUSTER_NETINTERFACE_NOT_FOUND: The cluster network interface was not found.")// ERROR_CLUSTER_NETINTERFACE_NOT_FOUND
        ERR(5048L, "ERROR_CLUSTER_INVALID_REQUEST: The cluster request is not valid for this object.")// ERROR_CLUSTER_INVALID_REQUEST
        ERR(5049L, "ERROR_CLUSTER_INVALID_NETWORK_PROVIDER: The cluster network provider is not valid.")// ERROR_CLUSTER_INVALID_NETWORK_PROVIDER
        ERR(5050L, "ERROR_CLUSTER_NODE_DOWN: The cluster node is down.")// ERROR_CLUSTER_NODE_DOWN
        ERR(5051L, "ERROR_CLUSTER_NODE_UNREACHABLE: The cluster node is not reachable.")// ERROR_CLUSTER_NODE_UNREACHABLE
        ERR(5052L, "ERROR_CLUSTER_NODE_NOT_MEMBER: The cluster node is not a member of the cluster.")// ERROR_CLUSTER_NODE_NOT_MEMBER
        ERR(5053L, "ERROR_CLUSTER_JOIN_NOT_IN_PROGRESS: A cluster join operation is not in progress.")// ERROR_CLUSTER_JOIN_NOT_IN_PROGRESS
        ERR(5054L, "ERROR_CLUSTER_INVALID_NETWORK: The cluster network is not valid.")// ERROR_CLUSTER_INVALID_NETWORK
        ERR(5056L, "ERROR_CLUSTER_NODE_UP: The cluster node is up.")// ERROR_CLUSTER_NODE_UP
        ERR(5057L, "ERROR_CLUSTER_IPADDR_IN_USE: The cluster IP address is already in use.")// ERROR_CLUSTER_IPADDR_IN_USE
        ERR(5058L, "ERROR_CLUSTER_NODE_NOT_PAUSED: The cluster node is not paused.")// ERROR_CLUSTER_NODE_NOT_PAUSED
        ERR(5059L, "ERROR_CLUSTER_NO_SECURITY_CONTEXT: No cluster security context is available.")// ERROR_CLUSTER_NO_SECURITY_CONTEXT
        ERR(5060L, "ERROR_CLUSTER_NETWORK_NOT_INTERNAL: The cluster network is not configured for internal cluster communication.")// ERROR_CLUSTER_NETWORK_NOT_INTERNAL
        ERR(5061L, "ERROR_CLUSTER_NODE_ALREADY_UP: The cluster node is already up.")// ERROR_CLUSTER_NODE_ALREADY_UP
        ERR(5062L, "ERROR_CLUSTER_NODE_ALREADY_DOWN: The cluster node is already down.")// ERROR_CLUSTER_NODE_ALREADY_DOWN
        ERR(5063L, "ERROR_CLUSTER_NETWORK_ALREADY_ONLINE: The cluster network is already online.")// ERROR_CLUSTER_NETWORK_ALREADY_ONLINE
        ERR(5064L, "ERROR_CLUSTER_NETWORK_ALREADY_OFFLINE: The cluster network is already offline.")// ERROR_CLUSTER_NETWORK_ALREADY_OFFLINE
        ERR(5065L, "ERROR_CLUSTER_NODE_ALREADY_MEMBER: The cluster node is already a member of the cluster.")// ERROR_CLUSTER_NODE_ALREADY_MEMBER
        ERR(5066L, "ERROR_CLUSTER_LAST_INTERNAL_NETWORK: The cluster network is the only one configured for internal cluster communication between two or more active cluster nodes. The internal communication capability cannot be removed from the network.")// ERROR_CLUSTER_LAST_INTERNAL_NETWORK
        ERR(5067L, "ERROR_CLUSTER_NETWORK_HAS_DEPENDENTS: One or more cluster resources depend on the network to provide service to clients. The client access capability cannot be removed from the network.")// ERROR_CLUSTER_NETWORK_HAS_DEPENDENTS
        ERR(5068L, "ERROR_INVALID_OPERATION_ON_QUORUM: This operation cannot be performed on the cluster resource as it the quorum resource. You may not bring the quorum resource offline or modify its possible owners list.")// ERROR_INVALID_OPERATION_ON_QUORUM
        ERR(5069L, "ERROR_DEPENDENCY_NOT_ALLOWED: The cluster quorum resource is not allowed to have any dependencies.")// ERROR_DEPENDENCY_NOT_ALLOWED
        ERR(5070L, "ERROR_CLUSTER_NODE_PAUSED: The cluster node is paused.")// ERROR_CLUSTER_NODE_PAUSED
        ERR(5071L, "ERROR_NODE_CANT_HOST_RESOURCE: The cluster resource cannot be brought online. The owner node cannot run this resource.")// ERROR_NODE_CANT_HOST_RESOURCE
        ERR(5072L, "ERROR_CLUSTER_NODE_NOT_READY: The cluster node is not ready to perform the requested operation.")// ERROR_CLUSTER_NODE_NOT_READY
        ERR(5073L, "ERROR_CLUSTER_NODE_SHUTTING_DOWN: The cluster node is shutting down.")// ERROR_CLUSTER_NODE_SHUTTING_DOWN
        ERR(5074L, "ERROR_CLUSTER_JOIN_ABORTED: The cluster join operation was aborted.")// ERROR_CLUSTER_JOIN_ABORTED
        ERR(5075L, "ERROR_CLUSTER_INCOMPATIBLE_VERSIONS: The cluster join operation failed due to incompatible software versions between the joining node and its sponsor.")// ERROR_CLUSTER_INCOMPATIBLE_VERSIONS
        ERR(5076L, "ERROR_CLUSTER_MAXNUM_OF_RESOURCES_EXCEEDED: This resource cannot be created because the cluster has reached the limit on the number of resources it can monitor.")// ERROR_CLUSTER_MAXNUM_OF_RESOURCES_EXCEEDED
        ERR(5077L, "ERROR_CLUSTER_SYSTEM_CONFIG_CHANGED: The system configuration changed during the cluster join or form operation. The join or form operation was aborted.")// ERROR_CLUSTER_SYSTEM_CONFIG_CHANGED
        ERR(5078L, "ERROR_CLUSTER_RESOURCE_TYPE_NOT_FOUND: The specified resource type was not found.")// ERROR_CLUSTER_RESOURCE_TYPE_NOT_FOUND
        ERR(5079L, "ERROR_CLUSTER_RESTYPE_NOT_SUPPORTED: The specified node does not support a resource of this type. This may be due to version inconsistencies or due to the absence of the resource DLL on this node.")// ERROR_CLUSTER_RESTYPE_NOT_SUPPORTED
        ERR(5080L, "ERROR_CLUSTER_RESNAME_NOT_FOUND: The specified resource name is not supported by this resource DLL. This may be due to a bad (or changed) name supplied to the resource DLL.")// ERROR_CLUSTER_RESNAME_NOT_FOUND
        ERR(5081L, "ERROR_CLUSTER_NO_RPC_PACKAGES_REGISTERED: No authentication package could be registered with the RPC server.")// ERROR_CLUSTER_NO_RPC_PACKAGES_REGISTERED
        ERR(5082L, "ERROR_CLUSTER_OWNER_NOT_IN_PREFLIST: You cannot bring the group online because the owner of the group is not in the preferred list for the group. To change the owner node for the group, move the group.")// ERROR_CLUSTER_OWNER_NOT_IN_PREFLIST
        ERR(5083L, "ERROR_CLUSTER_DATABASE_SEQMISMATCH: The join operation failed because the cluster database sequence number has changed or is incompatible with the locker node. This may happen during a join operation if the cluster database was changing during the join.")// ERROR_CLUSTER_DATABASE_SEQMISMATCH
        ERR(5084L, "ERROR_RESMON_INVALID_STATE: The resource monitor will not allow the fail operation to be performed while the resource is in its current state. This may happen if the resource is in a pending state.")// ERROR_RESMON_INVALID_STATE
        ERR(5085L, "ERROR_CLUSTER_GUM_NOT_LOCKER: A non locker code got a request to reserve the lock for making global updates.")// ERROR_CLUSTER_GUM_NOT_LOCKER
        ERR(5086L, "ERROR_QUORUM_DISK_NOT_FOUND: The quorum disk could not be located by the cluster service.")// ERROR_QUORUM_DISK_NOT_FOUND
        ERR(5087L, "ERROR_DATABASE_BACKUP_CORRUPT: The backed up cluster database is possibly corrupt.")// ERROR_DATABASE_BACKUP_CORRUPT
        ERR(5088L, "ERROR_CLUSTER_NODE_ALREADY_HAS_DFS_ROOT: A DFS root already exists in this cluster node.")// ERROR_CLUSTER_NODE_ALREADY_HAS_DFS_ROOT
        ERR(5089L, "ERROR_RESOURCE_PROPERTY_UNCHANGEABLE: An attempt to modify a resource property failed because it conflicts with another existing property.")// ERROR_RESOURCE_PROPERTY_UNCHANGEABLE
        ERR(6000L, "ERROR_ENCRYPTION_FAILED: The specified file could not be encrypted.")// ERROR_ENCRYPTION_FAILED
        ERR(6001L, "ERROR_DECRYPTION_FAILED: The specified file could not be decrypted.")// ERROR_DECRYPTION_FAILED
        ERR(6002L, "ERROR_FILE_ENCRYPTED: The specified file is encrypted and the user does not have the ability to decrypt it.")// ERROR_FILE_ENCRYPTED
        ERR(6003L, "ERROR_NO_RECOVERY_POLICY: There is no valid encryption recovery policy configured for this system.")// ERROR_NO_RECOVERY_POLICY
        ERR(6004L, "ERROR_NO_EFS: The required encryption driver is not loaded for this system.")// ERROR_NO_EFS
        ERR(6005L, "ERROR_WRONG_EFS: The file was encrypted with a different encryption driver than is currently loaded.")// ERROR_WRONG_EFS
        ERR(6006L, "ERROR_NO_USER_KEYS: There are no EFS keys defined for the user.")// ERROR_NO_USER_KEYS
        ERR(6007L, "ERROR_FILE_NOT_ENCRYPTED: The specified file is not encrypted.")// ERROR_FILE_NOT_ENCRYPTED
        ERR(6008L, "ERROR_NOT_EXPORT_FORMAT: The specified file is not in the defined EFS export format.")// ERROR_NOT_EXPORT_FORMAT
        ERR(6009L, "ERROR_FILE_READ_ONLY: The specified file is read only.")// ERROR_FILE_READ_ONLY
        ERR(6010L, "ERROR_DIR_EFS_DISALLOWED: The directory has been disabled for encryption.")// ERROR_DIR_EFS_DISALLOWED
        ERR(6011L, "ERROR_EFS_SERVER_NOT_TRUSTED: The server is not trusted for remote encryption operation.")// ERROR_EFS_SERVER_NOT_TRUSTED
        ERR(6012L, "ERROR_BAD_RECOVERY_POLICY: Recovery policy configured for this system contains invalid recovery certificate.")// ERROR_BAD_RECOVERY_POLICY
        ERR(6013L, "ERROR_EFS_ALG_BLOB_TOO_BIG: The encryption algorithm used on the source file needs a bigger key buffer than the one on the destination file.")// ERROR_EFS_ALG_BLOB_TOO_BIG
        ERR(6014L, "ERROR_VOLUME_NOT_SUPPORT_EFS: The disk partition does not support file encryption.")// ERROR_VOLUME_NOT_SUPPORT_EFS
        ERR(6200L, "SCHED_E_SERVICE_NOT_LOCALSYSTEM: The Task Scheduler service must be configured to run in the System account to function properly. Individual tasks may be configured to run in other accounts.")// SCHED_E_SERVICE_NOT_LOCALSYSTEM
        ERR(7001L, "ERROR_CTX_WINSTATION_NAME_INVALID: The specified session name is invalid.")// ERROR_CTX_WINSTATION_NAME_INVALID
        ERR(7002L, "ERROR_CTX_INVALID_PD: The specified protocol driver is invalid.")// ERROR_CTX_INVALID_PD
        ERR(7003L, "ERROR_CTX_PD_NOT_FOUND: The specified protocol driver was not found in the system path.")// ERROR_CTX_PD_NOT_FOUND
        ERR(7004L, "ERROR_CTX_WD_NOT_FOUND: The specified terminal connection driver was not found in the system path.")// ERROR_CTX_WD_NOT_FOUND
        ERR(7005L, "ERROR_CTX_CANNOT_MAKE_EVENTLOG_ENTRY: A registry key for event logging could not be created for this session.")// ERROR_CTX_CANNOT_MAKE_EVENTLOG_ENTRY
        ERR(7006L, "ERROR_CTX_SERVICE_NAME_COLLISION: A service with the same name already exists on the system.")// ERROR_CTX_SERVICE_NAME_COLLISION
        ERR(7007L, "ERROR_CTX_CLOSE_PENDING: A close operation is pending on the session.")// ERROR_CTX_CLOSE_PENDING
        ERR(7008L, "ERROR_CTX_NO_OUTBUF: There are no free output buffers available.")// ERROR_CTX_NO_OUTBUF
        ERR(7009L, "ERROR_CTX_MODEM_INF_NOT_FOUND: The MODEM.INF file was not found.")// ERROR_CTX_MODEM_INF_NOT_FOUND
        ERR(7010L, "ERROR_CTX_INVALID_MODEMNAME: The modem name was not found in MODEM.INF.")// ERROR_CTX_INVALID_MODEMNAME
        ERR(7011L, "ERROR_CTX_MODEM_RESPONSE_ERROR: The modem did not accept the command sent to it. Verify that the configured modem name matches the attached modem.")// ERROR_CTX_MODEM_RESPONSE_ERROR
        ERR(7012L, "ERROR_CTX_MODEM_RESPONSE_TIMEOUT: The modem did not respond to the command sent to it. Verify that the modem is properly cabled and powered on.")// ERROR_CTX_MODEM_RESPONSE_TIMEOUT
        ERR(7013L, "ERROR_CTX_MODEM_RESPONSE_NO_CARRIER: Carrier detect has failed or carrier has been dropped due to disconnect.")// ERROR_CTX_MODEM_RESPONSE_NO_CARRIER
        ERR(7014L, "ERROR_CTX_MODEM_RESPONSE_NO_DIALTONE: Dial tone not detected within the required time. Verify that the phone cable is properly attached and functional.")// ERROR_CTX_MODEM_RESPONSE_NO_DIALTONE
        ERR(7015L, "ERROR_CTX_MODEM_RESPONSE_BUSY: Busy signal detected at remote site on callback.")// ERROR_CTX_MODEM_RESPONSE_BUSY
        ERR(7016L, "ERROR_CTX_MODEM_RESPONSE_VOICE: Voice detected at remote site on callback.")// ERROR_CTX_MODEM_RESPONSE_VOICE
        ERR(7017L, "ERROR_CTX_TD_ERROR: Transport driver error")// ERROR_CTX_TD_ERROR
        ERR(7022L, "ERROR_CTX_WINSTATION_NOT_FOUND: The specified session cannot be found.")// ERROR_CTX_WINSTATION_NOT_FOUND
        ERR(7023L, "ERROR_CTX_WINSTATION_ALREADY_EXISTS: The specified session name is already in use.")// ERROR_CTX_WINSTATION_ALREADY_EXISTS
        ERR(7024L, "ERROR_CTX_WINSTATION_BUSY: The requested operation cannot be completed because the terminal connection is currently busy processing a connect, disconnect, reset, or delete operation.")// ERROR_CTX_WINSTATION_BUSY
        ERR(7025L, "ERROR_CTX_BAD_VIDEO_MODE: An attempt has been made to connect to a session whose video mode is not supported by the current client.")// ERROR_CTX_BAD_VIDEO_MODE
        ERR(7035L, "ERROR_CTX_GRAPHICS_INVALID: The application attempted to enable DOS graphics mode.")// ERROR_CTX_GRAPHICS_INVALID
        ERR(7037L, "ERROR_CTX_LOGON_DISABLED: Your interactive logon privilege has been disabled.")// ERROR_CTX_LOGON_DISABLED
        ERR(7038L, "ERROR_CTX_NOT_CONSOLE: The requested operation can be performed only on the system console.")// ERROR_CTX_NOT_CONSOLE
        ERR(7040L, "ERROR_CTX_CLIENT_QUERY_TIMEOUT: The client failed to respond to the server connect message.")// ERROR_CTX_CLIENT_QUERY_TIMEOUT
        ERR(7041L, "ERROR_CTX_CONSOLE_DISCONNECT: Disconnecting the console session is not supported.")// ERROR_CTX_CONSOLE_DISCONNECT
        ERR(7042L, "ERROR_CTX_CONSOLE_CONNECT: Reconnecting a disconnected session to the console is not supported.")// ERROR_CTX_CONSOLE_CONNECT
        ERR(7044L, "ERROR_CTX_SHADOW_DENIED: The request to control another session remotely was denied.")// ERROR_CTX_SHADOW_DENIED
        ERR(7045L, "ERROR_CTX_WINSTATION_ACCESS_DENIED: The requested session access is denied.")// ERROR_CTX_WINSTATION_ACCESS_DENIED
        ERR(7049L, "ERROR_CTX_INVALID_WD: The specified terminal connection driver is invalid.")// ERROR_CTX_INVALID_WD
        ERR(7050L, "ERROR_CTX_SHADOW_INVALID: The requested session cannot be controlled remotely.")// ERROR_CTX_SHADOW_INVALID
        ERR(7051L, "ERROR_CTX_SHADOW_DISABLED: The requested session is not configured to allow remote control.")// ERROR_CTX_SHADOW_DISABLED
        ERR(7052L, "ERROR_CTX_CLIENT_LICENSE_IN_USE: Your request to connect to this Terminal Server has been rejected. Your Terminal Server client license number is currently being used by another user.")// ERROR_CTX_CLIENT_LICENSE_IN_USE
        ERR(7053L, "ERROR_CTX_CLIENT_LICENSE_NOT_SET: Your request to connect to this Terminal Server has been rejected. Your Terminal Server client license number has not been entered for this copy of the Terminal Server client.")// ERROR_CTX_CLIENT_LICENSE_NOT_SET
        ERR(7054L, "ERROR_CTX_LICENSE_NOT_AVAILABLE: The system has reached its licensed logon limit.")// ERROR_CTX_LICENSE_NOT_AVAILABLE
        ERR(7055L, "ERROR_CTX_LICENSE_CLIENT_INVALID: The client you are using is not licensed to use this system. Your logon request is denied.")// ERROR_CTX_LICENSE_CLIENT_INVALID
        ERR(7056L, "ERROR_CTX_LICENSE_EXPIRED: The system license has expired. Your logon request is denied.")// ERROR_CTX_LICENSE_EXPIRED
        ERR(7057L, "ERROR_CTX_SHADOW_NOT_RUNNING: Remote control could not be terminated because the specified session is not currently being remotely controlled.")// ERROR_CTX_SHADOW_NOT_RUNNING
        ERR(8001L, "FRS_ERR_INVALID_API_SEQUENCE: The file replication service API was called incorrectly.")// FRS_ERR_INVALID_API_SEQUENCE
        ERR(8002L, "FRS_ERR_STARTING_SERVICE: The file replication service cannot be started.")// FRS_ERR_STARTING_SERVICE
        ERR(8003L, "FRS_ERR_STOPPING_SERVICE: The file replication service cannot be stopped.")// FRS_ERR_STOPPING_SERVICE
        ERR(8004L, "FRS_ERR_INTERNAL_API: The file replication service API terminated the request.")// FRS_ERR_INTERNAL_API
        ERR(8005L, "FRS_ERR_INTERNAL: The file replication service terminated the request.")// FRS_ERR_INTERNAL
        ERR(8006L, "FRS_ERR_SERVICE_COMM: The file replication service cannot be contacted.")// FRS_ERR_SERVICE_COMM
        ERR(8007L, "FRS_ERR_INSUFFICIENT_PRIV: The file replication service cannot satisfy the request because the user has insufficient privileges.")// FRS_ERR_INSUFFICIENT_PRIV
        ERR(8008L, "FRS_ERR_AUTHENTICATION: The file replication service cannot satisfy the request because authenticated RPC is not available.")// FRS_ERR_AUTHENTICATION
        ERR(8009L, "FRS_ERR_PARENT_INSUFFICIENT_PRIV: The file replication service cannot satisfy the request because the user has insufficient privileges on the domain controller.")// FRS_ERR_PARENT_INSUFFICIENT_PRIV
        ERR(8010L, "FRS_ERR_PARENT_AUTHENTICATION: The file replication service cannot satisfy the request because authenticated RPC is not available on the domain controller.")// FRS_ERR_PARENT_AUTHENTICATION
        ERR(8011L, "FRS_ERR_CHILD_TO_PARENT_COMM: The file replication service cannot communicate with the file replication service on the domain controller.")// FRS_ERR_CHILD_TO_PARENT_COMM
        ERR(8012L, "FRS_ERR_PARENT_TO_CHILD_COMM: The file replication service on the domain controller cannot communicate with the file replication service on this computer.")// FRS_ERR_PARENT_TO_CHILD_COMM
        ERR(8013L, "FRS_ERR_SYSVOL_POPULATE: The file replication service cannot populate the system volume because of an internal error.")// FRS_ERR_SYSVOL_POPULATE
        ERR(8014L, "FRS_ERR_SYSVOL_POPULATE_TIMEOUT: The file replication service cannot populate the system volume because of an internal timeout.")// FRS_ERR_SYSVOL_POPULATE_TIMEOUT
        ERR(8015L, "FRS_ERR_SYSVOL_IS_BUSY: The file replication service cannot process the request. The system volume is busy with a previous request.")// FRS_ERR_SYSVOL_IS_BUSY
        ERR(8016L, "FRS_ERR_SYSVOL_DEMOTE: The file replication service cannot stop replicating the system volume because of an internal error.")// FRS_ERR_SYSVOL_DEMOTE
        ERR(8017L, "FRS_ERR_INVALID_SERVICE_PARAMETER: The file replication service detected an invalid parameter.")// FRS_ERR_INVALID_SERVICE_PARAMETER
        ERR(8200L, "ERROR_DS_NOT_INSTALLED: An error occurred while installing the directory service. For more information, see the event log.")// ERROR_DS_NOT_INSTALLED
        ERR(8201L, "ERROR_DS_MEMBERSHIP_EVALUATED_LOCALLY: The directory service evaluated group memberships locally.")// ERROR_DS_MEMBERSHIP_EVALUATED_LOCALLY
        ERR(8202L, "ERROR_DS_NO_ATTRIBUTE_OR_VALUE: The specified directory service attribute or value does not exist.")// ERROR_DS_NO_ATTRIBUTE_OR_VALUE
        ERR(8203L, "ERROR_DS_INVALID_ATTRIBUTE_SYNTAX: The attribute syntax specified to the directory service is invalid.")// ERROR_DS_INVALID_ATTRIBUTE_SYNTAX
        ERR(8204L, "ERROR_DS_ATTRIBUTE_TYPE_UNDEFINED: The attribute type specified to the directory service is not defined.")// ERROR_DS_ATTRIBUTE_TYPE_UNDEFINED
        ERR(8205L, "ERROR_DS_ATTRIBUTE_OR_VALUE_EXISTS: The specified directory service attribute or value already exists.")// ERROR_DS_ATTRIBUTE_OR_VALUE_EXISTS
        ERR(8206L, "ERROR_DS_BUSY: The directory service is busy.")// ERROR_DS_BUSY
        ERR(8207L, "ERROR_DS_UNAVAILABLE: The directory service is unavailable.")// ERROR_DS_UNAVAILABLE
        ERR(8208L, "ERROR_DS_NO_RIDS_ALLOCATED: The directory service was unable to allocate a relative identifier.")// ERROR_DS_NO_RIDS_ALLOCATED
        ERR(8209L, "ERROR_DS_NO_MORE_RIDS: The directory service has exhausted the pool of relative identifiers.")// ERROR_DS_NO_MORE_RIDS
        ERR(8210L, "ERROR_DS_INCORRECT_ROLE_OWNER: The requested operation could not be performed because the directory service is not the master for that type of operation.")// ERROR_DS_INCORRECT_ROLE_OWNER
        ERR(8211L, "ERROR_DS_RIDMGR_INIT_ERROR: The directory service was unable to initialize the subsystem that allocates relative identifiers.")// ERROR_DS_RIDMGR_INIT_ERROR
        ERR(8212L, "ERROR_DS_OBJ_CLASS_VIOLATION: The requested operation did not satisfy one or more constraints associated with the class of the object.")// ERROR_DS_OBJ_CLASS_VIOLATION
        ERR(8213L, "ERROR_DS_CANT_ON_NON_LEAF: The directory service can perform the requested operation only on a leaf object.")// ERROR_DS_CANT_ON_NON_LEAF
        ERR(8214L, "ERROR_DS_CANT_ON_RDN: The directory service cannot perform the requested operation on the RDN attribute of an object.")// ERROR_DS_CANT_ON_RDN
        ERR(8215L, "ERROR_DS_CANT_MOD_OBJ_CLASS: The directory service detected an attempt to modify the object class of an object.")// ERROR_DS_CANT_MOD_OBJ_CLASS
        ERR(8216L, "ERROR_DS_CROSS_DOM_MOVE_ERROR: The requested cross-domain move operation could not be performed.")// ERROR_DS_CROSS_DOM_MOVE_ERROR
        ERR(8217L, "ERROR_DS_GC_NOT_AVAILABLE: Unable to contact the global catalog server.")// ERROR_DS_GC_NOT_AVAILABLE
        ERR(8218L, "ERROR_SHARED_POLICY: The policy object is shared and can only be modified at the root.")// ERROR_SHARED_POLICY
        ERR(8219L, "ERROR_POLICY_OBJECT_NOT_FOUND: The policy object does not exist.")// ERROR_POLICY_OBJECT_NOT_FOUND
        ERR(8220L, "ERROR_POLICY_ONLY_IN_DS: The requested policy information is only in the directory service.")// ERROR_POLICY_ONLY_IN_DS
        ERR(8221L, "ERROR_PROMOTION_ACTIVE: A domain controller promotion is currently active.")// ERROR_PROMOTION_ACTIVE
        ERR(8222L, "ERROR_NO_PROMOTION_ACTIVE: A domain controller promotion is not currently active")// ERROR_NO_PROMOTION_ACTIVE
        ERR(8224L, "ERROR_DS_OPERATIONS_ERROR: An operations error occurred.")// ERROR_DS_OPERATIONS_ERROR
        ERR(8225L, "ERROR_DS_PROTOCOL_ERROR: A protocol error occurred.")// ERROR_DS_PROTOCOL_ERROR
        ERR(8226L, "ERROR_DS_TIMELIMIT_EXCEEDED: The time limit for this request was exceeded.")// ERROR_DS_TIMELIMIT_EXCEEDED
        ERR(8227L, "ERROR_DS_SIZELIMIT_EXCEEDED: The size limit for this request was exceeded.")// ERROR_DS_SIZELIMIT_EXCEEDED
        ERR(8228L, "ERROR_DS_ADMIN_LIMIT_EXCEEDED: The administrative limit for this request was exceeded.")// ERROR_DS_ADMIN_LIMIT_EXCEEDED
        ERR(8229L, "ERROR_DS_COMPARE_FALSE: The compare response was false.")// ERROR_DS_COMPARE_FALSE
        ERR(8230L, "ERROR_DS_COMPARE_TRUE: The compare response was true.")// ERROR_DS_COMPARE_TRUE
        ERR(8231L, "ERROR_DS_AUTH_METHOD_NOT_SUPPORTED: The requested authentication method is not supported by the server.")// ERROR_DS_AUTH_METHOD_NOT_SUPPORTED
        ERR(8232L, "ERROR_DS_STRONG_AUTH_REQUIRED: A more secure authentication method is required for this server.")// ERROR_DS_STRONG_AUTH_REQUIRED
        ERR(8233L, "ERROR_DS_INAPPROPRIATE_AUTH: Inappropriate authentication.")// ERROR_DS_INAPPROPRIATE_AUTH
        ERR(8234L, "ERROR_DS_AUTH_UNKNOWN: The authentication mechanism is unknown.")// ERROR_DS_AUTH_UNKNOWN
        ERR(8235L, "ERROR_DS_REFERRAL: A referral was returned from the server.")// ERROR_DS_REFERRAL
        ERR(8236L, "ERROR_DS_UNAVAILABLE_CRIT_EXTENSION: The server does not support the requested critical extension.")// ERROR_DS_UNAVAILABLE_CRIT_EXTENSION
        ERR(8237L, "ERROR_DS_CONFIDENTIALITY_REQUIRED: This request requires a secure connection.")// ERROR_DS_CONFIDENTIALITY_REQUIRED
        ERR(8238L, "ERROR_DS_INAPPROPRIATE_MATCHING: Inappropriate matching.")// ERROR_DS_INAPPROPRIATE_MATCHING
        ERR(8239L, "ERROR_DS_CONSTRAINT_VIOLATION: A constraint violation occurred.")// ERROR_DS_CONSTRAINT_VIOLATION
        ERR(8240L, "ERROR_DS_NO_SUCH_OBJECT: There is no such object on the server.")// ERROR_DS_NO_SUCH_OBJECT
        ERR(8241L, "ERROR_DS_ALIAS_PROBLEM: There is an alias problem.")// ERROR_DS_ALIAS_PROBLEM
        ERR(8242L, "ERROR_DS_INVALID_DN_SYNTAX: An invalid dn syntax has been specified.")// ERROR_DS_INVALID_DN_SYNTAX
        ERR(8243L, "ERROR_DS_IS_LEAF: The object is a leaf object.")// ERROR_DS_IS_LEAF
        ERR(8244L, "ERROR_DS_ALIAS_DEREF_PROBLEM: There is an alias dereferencing problem.")// ERROR_DS_ALIAS_DEREF_PROBLEM
        ERR(8245L, "ERROR_DS_UNWILLING_TO_PERFORM: The server is unwilling to process the request.")// ERROR_DS_UNWILLING_TO_PERFORM
        ERR(8246L, "ERROR_DS_LOOP_DETECT: A loop has been detected.")// ERROR_DS_LOOP_DETECT
        ERR(8247L, "ERROR_DS_NAMING_VIOLATION: There is a naming violation.")// ERROR_DS_NAMING_VIOLATION
        ERR(8248L, "ERROR_DS_OBJECT_RESULTS_TOO_LARGE: The result set is too large.")// ERROR_DS_OBJECT_RESULTS_TOO_LARGE
        ERR(8249L, "ERROR_DS_AFFECTS_MULTIPLE_DSAS: The operation affects multiple DSAs")// ERROR_DS_AFFECTS_MULTIPLE_DSAS
        ERR(8250L, "ERROR_DS_SERVER_DOWN: The server is not operational.")// ERROR_DS_SERVER_DOWN
        ERR(8251L, "ERROR_DS_LOCAL_ERROR: A local error has occurred.")// ERROR_DS_LOCAL_ERROR
        ERR(8252L, "ERROR_DS_ENCODING_ERROR: An encoding error has occurred.")// ERROR_DS_ENCODING_ERROR
        ERR(8253L, "ERROR_DS_DECODING_ERROR: A decoding error has occurred.")// ERROR_DS_DECODING_ERROR
        ERR(8254L, "ERROR_DS_FILTER_UNKNOWN: The search filter cannot be recognized.")// ERROR_DS_FILTER_UNKNOWN
        ERR(8255L, "ERROR_DS_PARAM_ERROR: One or more parameters are illegal.")// ERROR_DS_PARAM_ERROR
        ERR(8256L, "ERROR_DS_NOT_SUPPORTED: The specified method is not supported.")// ERROR_DS_NOT_SUPPORTED
        ERR(8257L, "ERROR_DS_NO_RESULTS_RETURNED: No results were returned.")// ERROR_DS_NO_RESULTS_RETURNED
        ERR(8258L, "ERROR_DS_CONTROL_NOT_FOUND: The specified control is not supported by the server.")// ERROR_DS_CONTROL_NOT_FOUND
        ERR(8259L, "ERROR_DS_CLIENT_LOOP: A referral loop was detected by the client.")// ERROR_DS_CLIENT_LOOP
        ERR(8260L, "ERROR_DS_REFERRAL_LIMIT_EXCEEDED: The preset referral limit was exceeded.")// ERROR_DS_REFERRAL_LIMIT_EXCEEDED
        ERR(8261L, "ERROR_DS_SORT_CONTROL_MISSING: The search requires a SORT control.")// ERROR_DS_SORT_CONTROL_MISSING
        ERR(8262L, "ERROR_DS_OFFSET_RANGE_ERROR: The search results exceed the offset range specified.")// ERROR_DS_OFFSET_RANGE_ERROR
        ERR(8301L, "ERROR_DS_ROOT_MUST_BE_NC: The root object must be the head of a naming context. The root object cannot have an instantiated parent.")// ERROR_DS_ROOT_MUST_BE_NC
        ERR(8302L, "ERROR_DS_ADD_REPLICA_INHIBITED: The add replica operation cannot be performed. The naming context must be writable in order to create the replica.")// ERROR_DS_ADD_REPLICA_INHIBITED
        ERR(8303L, "ERROR_DS_ATT_NOT_DEF_IN_SCHEMA: A reference to an attribute that is not defined in the schema occurred.")// ERROR_DS_ATT_NOT_DEF_IN_SCHEMA
        ERR(8304L, "ERROR_DS_MAX_OBJ_SIZE_EXCEEDED: The maximum size of an object has been exceeded.")// ERROR_DS_MAX_OBJ_SIZE_EXCEEDED
        ERR(8305L, "ERROR_DS_OBJ_STRING_NAME_EXISTS: An attempt was made to add an object to the directory with a name that is already in use.")// ERROR_DS_OBJ_STRING_NAME_EXISTS
        ERR(8306L, "ERROR_DS_NO_RDN_DEFINED_IN_SCHEMA: An attempt was made to add an object of a class that does not have an RDN defined in the schema.")// ERROR_DS_NO_RDN_DEFINED_IN_SCHEMA
        ERR(8307L, "ERROR_DS_RDN_DOESNT_MATCH_SCHEMA: An attempt was made to add an object using an RDN that is not the RDN defined in the schema.")// ERROR_DS_RDN_DOESNT_MATCH_SCHEMA
        ERR(8308L, "ERROR_DS_NO_REQUESTED_ATTS_FOUND: None of the requested attributes were found on the objects.")// ERROR_DS_NO_REQUESTED_ATTS_FOUND
        ERR(8309L, "ERROR_DS_USER_BUFFER_TO_SMALL: The user buffer is too small.")// ERROR_DS_USER_BUFFER_TO_SMALL
        ERR(8310L, "ERROR_DS_ATT_IS_NOT_ON_OBJ: The attribute specified in the operation is not present on the object.")// ERROR_DS_ATT_IS_NOT_ON_OBJ
        ERR(8311L, "ERROR_DS_ILLEGAL_MOD_OPERATION: Illegal modify operation. Some aspect of the modification is not permitted.")// ERROR_DS_ILLEGAL_MOD_OPERATION
        ERR(8312L, "ERROR_DS_OBJ_TOO_LARGE: The specified object is too large.")// ERROR_DS_OBJ_TOO_LARGE
        ERR(8313L, "ERROR_DS_BAD_INSTANCE_TYPE: The specified instance type is not valid.")// ERROR_DS_BAD_INSTANCE_TYPE
        ERR(8314L, "ERROR_DS_MASTERDSA_REQUIRED: The operation must be performed at a master DSA.")// ERROR_DS_MASTERDSA_REQUIRED
        ERR(8315L, "ERROR_DS_OBJECT_CLASS_REQUIRED: The object class attribute must be specified.")// ERROR_DS_OBJECT_CLASS_REQUIRED
        ERR(8316L, "ERROR_DS_MISSING_REQUIRED_ATT: A required attribute is missing.")// ERROR_DS_MISSING_REQUIRED_ATT
        ERR(8317L, "ERROR_DS_ATT_NOT_DEF_FOR_CLASS: An attempt was made to modify an object to include an attribute that is not legal for its class.")// ERROR_DS_ATT_NOT_DEF_FOR_CLASS
        ERR(8318L, "ERROR_DS_ATT_ALREADY_EXISTS: The specified attribute is already present on the object.")// ERROR_DS_ATT_ALREADY_EXISTS
        ERR(8320L, "ERROR_DS_CANT_ADD_ATT_VALUES: The specified attribute is not present, or has no values.")// ERROR_DS_CANT_ADD_ATT_VALUES
        ERR(8321L, "ERROR_DS_SINGLE_VALUE_CONSTRAINT: Mutliple values were specified for an attribute that can have only one value.")// ERROR_DS_SINGLE_VALUE_CONSTRAINT
        ERR(8322L, "ERROR_DS_RANGE_CONSTRAINT: A value for the attribute was not in the acceptable range of values.")// ERROR_DS_RANGE_CONSTRAINT
        ERR(8323L, "ERROR_DS_ATT_VAL_ALREADY_EXISTS: The specified value already exists.")// ERROR_DS_ATT_VAL_ALREADY_EXISTS
        ERR(8324L, "ERROR_DS_CANT_REM_MISSING_ATT: The attribute cannot be removed because it is not present on the object.")// ERROR_DS_CANT_REM_MISSING_ATT
        ERR(8325L, "ERROR_DS_CANT_REM_MISSING_ATT_VAL: The attribute value cannot be removed because it is not present on the object.")// ERROR_DS_CANT_REM_MISSING_ATT_VAL
        ERR(8326L, "ERROR_DS_ROOT_CANT_BE_SUBREF: The specified root object cannot be a subref.")// ERROR_DS_ROOT_CANT_BE_SUBREF
        ERR(8327L, "ERROR_DS_NO_CHAINING: Chaining is not permitted.")// ERROR_DS_NO_CHAINING
        ERR(8328L, "ERROR_DS_NO_CHAINED_EVAL: Chained evaluation is not permitted.")// ERROR_DS_NO_CHAINED_EVAL
        ERR(8329L, "ERROR_DS_NO_PARENT_OBJECT: The operation could not be performed because the object's parent is either uninstantiated or deleted.")// ERROR_DS_NO_PARENT_OBJECT
        ERR(8330L, "ERROR_DS_PARENT_IS_AN_ALIAS: Having a parent that is an alias is not permitted. Aliases are leaf objects.")// ERROR_DS_PARENT_IS_AN_ALIAS
        ERR(8331L, "ERROR_DS_CANT_MIX_MASTER_AND_REPS: The object and parent must be of the same type, either both masters or")// ERROR_DS_CANT_MIX_MASTER_AND_REPS
        ERR(8332L, "ERROR_DS_CHILDREN_EXIST: The operation cannot be performed because child objects exist. This operation can only be performed on a leaf object.")// ERROR_DS_CHILDREN_EXIST
        ERR(8333L, "ERROR_DS_OBJ_NOT_FOUND: Directory object not found.")// ERROR_DS_OBJ_NOT_FOUND
        ERR(8334L, "ERROR_DS_ALIASED_OBJ_MISSING: The aliased object is missing.")// ERROR_DS_ALIASED_OBJ_MISSING
        ERR(8335L, "ERROR_DS_BAD_NAME_SYNTAX: The object name has bad syntax.")// ERROR_DS_BAD_NAME_SYNTAX
        ERR(8336L, "ERROR_DS_ALIAS_POINTS_TO_ALIAS: It is not permitted for an alias to refer to another alias.")// ERROR_DS_ALIAS_POINTS_TO_ALIAS
        ERR(8337L, "ERROR_DS_CANT_DEREF_ALIAS: The alias cannot be dereferenced.")// ERROR_DS_CANT_DEREF_ALIAS
        ERR(8338L, "ERROR_DS_OUT_OF_SCOPE: The operation is out of scope.")// ERROR_DS_OUT_OF_SCOPE
        ERR(8340L, "ERROR_DS_CANT_DELETE_DSA_OBJ: The DSA object cannot be deleted.")// ERROR_DS_CANT_DELETE_DSA_OBJ
        ERR(8341L, "ERROR_DS_GENERIC_ERROR: A directory service error has occurred.")// ERROR_DS_GENERIC_ERROR
        ERR(8342L, "ERROR_DS_DSA_MUST_BE_INT_MASTER: The operation can only be performed on an internal master DSA object.")// ERROR_DS_DSA_MUST_BE_INT_MASTER
        ERR(8343L, "ERROR_DS_CLASS_NOT_DSA: The object must be of class DSA.")// ERROR_DS_CLASS_NOT_DSA
        ERR(8344L, "ERROR_DS_INSUFF_ACCESS_RIGHTS: Insufficient access rights to perform the operation.")// ERROR_DS_INSUFF_ACCESS_RIGHTS
        ERR(8345L, "ERROR_DS_ILLEGAL_SUPERIOR: The object cannot be added because the parent is not on the list of possible superiors.")// ERROR_DS_ILLEGAL_SUPERIOR
        ERR(8346L, "ERROR_DS_ATTRIBUTE_OWNED_BY_SAM: Access to the attribute is not permitted because the attribute is owned by the Security Accounts Manager (SAM).")// ERROR_DS_ATTRIBUTE_OWNED_BY_SAM
        ERR(8347L, "ERROR_DS_NAME_TOO_MANY_PARTS: The name has too many parts.")// ERROR_DS_NAME_TOO_MANY_PARTS
        ERR(8348L, "ERROR_DS_NAME_TOO_LONG: The name is too long.")// ERROR_DS_NAME_TOO_LONG
        ERR(8349L, "ERROR_DS_NAME_VALUE_TOO_LONG: The name value is too long.")// ERROR_DS_NAME_VALUE_TOO_LONG
        ERR(8350L, "ERROR_DS_NAME_UNPARSEABLE: The directory service encountered an error parsing a name.")// ERROR_DS_NAME_UNPARSEABLE
        ERR(8351L, "ERROR_DS_NAME_TYPE_UNKNOWN: The directory service cannot get the attribute type for a name.")// ERROR_DS_NAME_TYPE_UNKNOWN
        ERR(8352L, "ERROR_DS_NOT_AN_OBJECT: The name does not identify an object; the name identifies a phantom.")// ERROR_DS_NOT_AN_OBJECT
        ERR(8353L, "ERROR_DS_SEC_DESC_TOO_SHORT: The security descriptor is too short.")// ERROR_DS_SEC_DESC_TOO_SHORT
        ERR(8354L, "ERROR_DS_SEC_DESC_INVALID: The security descriptor is invalid.")// ERROR_DS_SEC_DESC_INVALID
        ERR(8355L, "ERROR_DS_NO_DELETED_NAME: Failed to create name for deleted object.")// ERROR_DS_NO_DELETED_NAME
        ERR(8356L, "ERROR_DS_SUBREF_MUST_HAVE_PARENT: The parent of a new subref must exist.")// ERROR_DS_SUBREF_MUST_HAVE_PARENT
        ERR(8357L, "ERROR_DS_NCNAME_MUST_BE_NC: The object must be a naming context.")// ERROR_DS_NCNAME_MUST_BE_NC
        ERR(8358L, "ERROR_DS_CANT_ADD_SYSTEM_ONLY: It is not permitted to add an attribute which is owned by the system.")// ERROR_DS_CANT_ADD_SYSTEM_ONLY
        ERR(8359L, "ERROR_DS_CLASS_MUST_BE_CONCRETE: The class of the object must be structural; you cannot instantiate an abstract class.")// ERROR_DS_CLASS_MUST_BE_CONCRETE
        ERR(8360L, "ERROR_DS_INVALID_DMD: The schema object could not be found.")// ERROR_DS_INVALID_DMD
        ERR(8361L, "ERROR_DS_OBJ_GUID_EXISTS: A local object with this GUID (dead or alive) already exists.")// ERROR_DS_OBJ_GUID_EXISTS
        ERR(8362L, "ERROR_DS_NOT_ON_BACKLINK: The operation cannot be performed on a back link.")// ERROR_DS_NOT_ON_BACKLINK
        ERR(8363L, "ERROR_DS_NO_CROSSREF_FOR_NC: The cross reference for the specified naming context could not be found.")// ERROR_DS_NO_CROSSREF_FOR_NC
        ERR(8364L, "ERROR_DS_SHUTTING_DOWN: The operation could not be performed because the directory service is shutting down.")// ERROR_DS_SHUTTING_DOWN
        ERR(8365L, "ERROR_DS_UNKNOWN_OPERATION: The directory service request is invalid.")// ERROR_DS_UNKNOWN_OPERATION
        ERR(8366L, "ERROR_DS_INVALID_ROLE_OWNER: The role owner attribute could not be read.")// ERROR_DS_INVALID_ROLE_OWNER
        ERR(8367L, "ERROR_DS_COULDNT_CONTACT_FSMO: The requested FSMO operation failed. The current FSMO holder could not be contacted.")// ERROR_DS_COULDNT_CONTACT_FSMO
        ERR(8368L, "ERROR_DS_CROSS_NC_DN_RENAME: Modification of a DN across a naming context is not permitted.")// ERROR_DS_CROSS_NC_DN_RENAME
        ERR(8369L, "ERROR_DS_CANT_MOD_SYSTEM_ONLY: The attribute cannot be modified because it is owned by the system.")// ERROR_DS_CANT_MOD_SYSTEM_ONLY
        ERR(8370L, "ERROR_DS_REPLICATOR_ONLY: Only the replicator can perform this function.")// ERROR_DS_REPLICATOR_ONLY
        ERR(8371L, "ERROR_DS_OBJ_CLASS_NOT_DEFINED: The specified class is not defined.")// ERROR_DS_OBJ_CLASS_NOT_DEFINED
        ERR(8372L, "ERROR_DS_OBJ_CLASS_NOT_SUBCLASS: The specified class is not a subclass.")// ERROR_DS_OBJ_CLASS_NOT_SUBCLASS
        ERR(8373L, "ERROR_DS_NAME_REFERENCE_INVALID: The name reference is invalid.")// ERROR_DS_NAME_REFERENCE_INVALID
        ERR(8374L, "ERROR_DS_CROSS_REF_EXISTS: A cross reference already exists.")// ERROR_DS_CROSS_REF_EXISTS
        ERR(8375L, "ERROR_DS_CANT_DEL_MASTER_CROSSREF: It is not permitted to delete a master cross reference.")// ERROR_DS_CANT_DEL_MASTER_CROSSREF
        ERR(8376L, "ERROR_DS_SUBTREE_NOTIFY_NOT_NC_HEAD: Subtree notifications are only supported on NC heads.")// ERROR_DS_SUBTREE_NOTIFY_NOT_NC_HEAD
        ERR(8377L, "ERROR_DS_NOTIFY_FILTER_TOO_COMPLEX: Notification filter is too complex.")// ERROR_DS_NOTIFY_FILTER_TOO_COMPLEX
        ERR(8378L, "ERROR_DS_DUP_RDN: Schema update failed: duplicate RDN.")// ERROR_DS_DUP_RDN
        ERR(8379L, "ERROR_DS_DUP_OID: Schema update failed: duplicate OID.")// ERROR_DS_DUP_OID
        ERR(8380L, "ERROR_DS_DUP_MAPI_ID: Schema update failed: duplicate MAPI identifier.")// ERROR_DS_DUP_MAPI_ID
        ERR(8381L, "ERROR_DS_DUP_SCHEMA_ID_GUID: Schema update failed: duplicate schema-id GUID.")// ERROR_DS_DUP_SCHEMA_ID_GUID
        ERR(8382L, "ERROR_DS_DUP_LDAP_DISPLAY_NAME: Schema update failed: duplicate LDAP display name.")// ERROR_DS_DUP_LDAP_DISPLAY_NAME
        ERR(8383L, "ERROR_DS_SEMANTIC_ATT_TEST: Schema update failed: range-lower less than range upper.")// ERROR_DS_SEMANTIC_ATT_TEST
        ERR(8384L, "ERROR_DS_SYNTAX_MISMATCH: Schema update failed: syntax mismatch.")// ERROR_DS_SYNTAX_MISMATCH
        ERR(8385L, "ERROR_DS_EXISTS_IN_MUST_HAVE: Schema deletion failed: attribute is used in must-contain.")// ERROR_DS_EXISTS_IN_MUST_HAVE
        ERR(8386L, "ERROR_DS_EXISTS_IN_MAY_HAVE: Schema deletion failed: attribute is used in may-contain.")// ERROR_DS_EXISTS_IN_MAY_HAVE
        ERR(8387L, "ERROR_DS_NONEXISTENT_MAY_HAVE: Schema update failed: attribute in may-contain does not exist.")// ERROR_DS_NONEXISTENT_MAY_HAVE
        ERR(8388L, "ERROR_DS_NONEXISTENT_MUST_HAVE: Schema update failed: attribute in must-contain does not exist.")// ERROR_DS_NONEXISTENT_MUST_HAVE
        ERR(8389L, "ERROR_DS_AUX_CLS_TEST_FAIL: Schema update failed: class in aux-class list does not exist or is not an auxiliary class.")// ERROR_DS_AUX_CLS_TEST_FAIL
        ERR(8390L, "ERROR_DS_NONEXISTENT_POSS_SUP: Schema update failed: class in poss-superiors does not exist.")// ERROR_DS_NONEXISTENT_POSS_SUP
        ERR(8391L, "ERROR_DS_SUB_CLS_TEST_FAIL: Schema update failed: class in subclassof list does not exist or does not satisfy hierarchy rules.")// ERROR_DS_SUB_CLS_TEST_FAIL
        ERR(8392L, "ERROR_DS_BAD_RDN_ATT_ID_SYNTAX: Schema update failed: Rdn-Att-Id has wrong syntax.")// ERROR_DS_BAD_RDN_ATT_ID_SYNTAX
        ERR(8393L, "ERROR_DS_EXISTS_IN_AUX_CLS: Schema deletion failed: class is used as auxiliary class.")// ERROR_DS_EXISTS_IN_AUX_CLS
        ERR(8394L, "ERROR_DS_EXISTS_IN_SUB_CLS: Schema deletion failed: class is used as sub class.")// ERROR_DS_EXISTS_IN_SUB_CLS
        ERR(8395L, "ERROR_DS_EXISTS_IN_POSS_SUP: Schema deletion failed: class is used as poss superior.")// ERROR_DS_EXISTS_IN_POSS_SUP
        ERR(8396L, "ERROR_DS_RECALCSCHEMA_FAILED: Schema update failed in recalculating validation cache.")// ERROR_DS_RECALCSCHEMA_FAILED
        ERR(8397L, "ERROR_DS_TREE_DELETE_NOT_FINISHED: The tree deletion is not finished. The request must be made again to continue deleting the tree.")// ERROR_DS_TREE_DELETE_NOT_FINISHED
        ERR(8398L, "ERROR_DS_CANT_DELETE: The requested delete operation could not be performed.")// ERROR_DS_CANT_DELETE
        ERR(8399L, "ERROR_DS_ATT_SCHEMA_REQ_ID: Cannot read the governs class identifier for the schema record.")// ERROR_DS_ATT_SCHEMA_REQ_ID
        ERR(8400L, "ERROR_DS_BAD_ATT_SCHEMA_SYNTAX: The attribute schema has bad syntax.")// ERROR_DS_BAD_ATT_SCHEMA_SYNTAX
        ERR(8401L, "ERROR_DS_CANT_CACHE_ATT: The attribute could not be cached.")// ERROR_DS_CANT_CACHE_ATT
        ERR(8402L, "ERROR_DS_CANT_CACHE_CLASS: The class could not be cached.")// ERROR_DS_CANT_CACHE_CLASS
        ERR(8403L, "ERROR_DS_CANT_REMOVE_ATT_CACHE: The attribute could not be removed from the cache.")// ERROR_DS_CANT_REMOVE_ATT_CACHE
        ERR(8404L, "ERROR_DS_CANT_REMOVE_CLASS_CACHE: The class could not be removed from the cache.")// ERROR_DS_CANT_REMOVE_CLASS_CACHE
        ERR(8405L, "ERROR_DS_CANT_RETRIEVE_DN: The distinguished name attribute could not be read.")// ERROR_DS_CANT_RETRIEVE_DN
        ERR(8406L, "ERROR_DS_MISSING_SUPREF: A required subref is missing.")// ERROR_DS_MISSING_SUPREF
        ERR(8407L, "ERROR_DS_CANT_RETRIEVE_INSTANCE: The instance type attribute could not be retrieved.")// ERROR_DS_CANT_RETRIEVE_INSTANCE
        ERR(8408L, "ERROR_DS_CODE_INCONSISTENCY: An internal error has occurred.")// ERROR_DS_CODE_INCONSISTENCY
        ERR(8409L, "ERROR_DS_DATABASE_ERROR: A database error has occurred.")// ERROR_DS_DATABASE_ERROR
        ERR(8410L, "ERROR_DS_GOVERNSID_MISSING: The attribute GOVERNSID is missing.")// ERROR_DS_GOVERNSID_MISSING
        ERR(8411L, "ERROR_DS_MISSING_EXPECTED_ATT: An expected attribute is missing.")// ERROR_DS_MISSING_EXPECTED_ATT
        ERR(8412L, "ERROR_DS_NCNAME_MISSING_CR_REF: The specified naming context is missing a cross reference.")// ERROR_DS_NCNAME_MISSING_CR_REF
        ERR(8413L, "ERROR_DS_SECURITY_CHECKING_ERROR: A security checking error has occurred.")// ERROR_DS_SECURITY_CHECKING_ERROR
        ERR(8414L, "ERROR_DS_SCHEMA_NOT_LOADED: The schema is not loaded.")// ERROR_DS_SCHEMA_NOT_LOADED
        ERR(8415L, "ERROR_DS_SCHEMA_ALLOC_FAILED: Schema allocation failed. Please check if the machine is running low on memory.")// ERROR_DS_SCHEMA_ALLOC_FAILED
        ERR(8416L, "ERROR_DS_ATT_SCHEMA_REQ_SYNTAX: Failed to obtain the required syntax for the attribute schema.")// ERROR_DS_ATT_SCHEMA_REQ_SYNTAX
        ERR(8417L, "ERROR_DS_GCVERIFY_ERROR: The global catalog verification failed. The global catalog is not available or does not support the operation. Some part of the directory is currently not available.")// ERROR_DS_GCVERIFY_ERROR
        ERR(8418L, "ERROR_DS_DRA_SCHEMA_MISMATCH: The replication operation failed because of a schema mismatch between the servers involved.")// ERROR_DS_DRA_SCHEMA_MISMATCH
        ERR(8419L, "ERROR_DS_CANT_FIND_DSA_OBJ: The DSA object could not be found.")// ERROR_DS_CANT_FIND_DSA_OBJ
        ERR(8420L, "ERROR_DS_CANT_FIND_EXPECTED_NC: The naming context could not be found.")// ERROR_DS_CANT_FIND_EXPECTED_NC
        ERR(8421L, "ERROR_DS_CANT_FIND_NC_IN_CACHE: The naming context could not be found in the cache.")// ERROR_DS_CANT_FIND_NC_IN_CACHE
        ERR(8422L, "ERROR_DS_CANT_RETRIEVE_CHILD: The child object could not be retrieved.")// ERROR_DS_CANT_RETRIEVE_CHILD
        ERR(8423L, "ERROR_DS_SECURITY_ILLEGAL_MODIFY: The modification was not permitted for security reasons.")// ERROR_DS_SECURITY_ILLEGAL_MODIFY
        ERR(8424L, "ERROR_DS_CANT_REPLACE_HIDDEN_REC: The operation cannot replace the hidden record.")// ERROR_DS_CANT_REPLACE_HIDDEN_REC
        ERR(8425L, "ERROR_DS_BAD_HIERARCHY_FILE: The hierarchy file is invalid.")// ERROR_DS_BAD_HIERARCHY_FILE
        ERR(8426L, "ERROR_DS_BUILD_HIERARCHY_TABLE_FAILED: The attempt to build the hierarchy table failed.")// ERROR_DS_BUILD_HIERARCHY_TABLE_FAILED
        ERR(8427L, "ERROR_DS_CONFIG_PARAM_MISSING: The directory configuration parameter is missing from the registry.")// ERROR_DS_CONFIG_PARAM_MISSING
        ERR(8428L, "ERROR_DS_COUNTING_AB_INDICES_FAILED: The attempt to count the address book indices failed.")// ERROR_DS_COUNTING_AB_INDICES_FAILED
        ERR(8429L, "ERROR_DS_HIERARCHY_TABLE_MALLOC_FAILED: The allocation of the hierarchy table failed.")// ERROR_DS_HIERARCHY_TABLE_MALLOC_FAILED
        ERR(8430L, "ERROR_DS_INTERNAL_FAILURE: The directory service encountered an internal failure.")// ERROR_DS_INTERNAL_FAILURE
        ERR(8431L, "ERROR_DS_UNKNOWN_ERROR: The directory service encountered an unknown failure.")// ERROR_DS_UNKNOWN_ERROR
        ERR(8432L, "ERROR_DS_ROOT_REQUIRES_CLASS_TOP: A root object requires a class of 'top'.")// ERROR_DS_ROOT_REQUIRES_CLASS_TOP
        ERR(8433L, "ERROR_DS_REFUSING_FSMO_ROLES: This directory server is shutting down, and cannot take ownership of new floating single-master operation roles.")// ERROR_DS_REFUSING_FSMO_ROLES
        ERR(8434L, "ERROR_DS_MISSING_FSMO_SETTINGS: The directory service is missing mandatory configuration information, and is unable to determine the ownership of floating single-master operation roles.")// ERROR_DS_MISSING_FSMO_SETTINGS
        ERR(8435L, "ERROR_DS_UNABLE_TO_SURRENDER_ROLES: The directory service was unable to transfer ownership of one or more floating single-master operation roles to other servers.")// ERROR_DS_UNABLE_TO_SURRENDER_ROLES
        ERR(8436L, "ERROR_DS_DRA_GENERIC: The replication operation failed.")// ERROR_DS_DRA_GENERIC
        ERR(8437L, "ERROR_DS_DRA_INVALID_PARAMETER: An invalid parameter was specified for this replication operation.")// ERROR_DS_DRA_INVALID_PARAMETER
        ERR(8438L, "ERROR_DS_DRA_BUSY: The directory service is too busy to complete the replication operation at this time.")// ERROR_DS_DRA_BUSY
        ERR(8439L, "ERROR_DS_DRA_BAD_DN: The distinguished name specified for this replication operation is invalid.")// ERROR_DS_DRA_BAD_DN
        ERR(8440L, "ERROR_DS_DRA_BAD_NC: The naming context specified for this replication operation is invalid.")// ERROR_DS_DRA_BAD_NC
        ERR(8441L, "ERROR_DS_DRA_DN_EXISTS: The distinguished name specified for this replication operation already exists.")// ERROR_DS_DRA_DN_EXISTS
        ERR(8442L, "ERROR_DS_DRA_INTERNAL_ERROR: The replication system encountered an internal error.")// ERROR_DS_DRA_INTERNAL_ERROR
        ERR(8443L, "ERROR_DS_DRA_INCONSISTENT_DIT: The replication operation encountered a database inconsistency.")// ERROR_DS_DRA_INCONSISTENT_DIT
        ERR(8444L, "ERROR_DS_DRA_CONNECTION_FAILED: The server specified for this replication operation could not be contacted.")// ERROR_DS_DRA_CONNECTION_FAILED
        ERR(8445L, "ERROR_DS_DRA_BAD_INSTANCE_TYPE: The replication operation encountered an object with an invalid instance type.")// ERROR_DS_DRA_BAD_INSTANCE_TYPE
        ERR(8446L, "ERROR_DS_DRA_OUT_OF_MEM: The replication operation failed to allocate memory.")// ERROR_DS_DRA_OUT_OF_MEM
        ERR(8447L, "ERROR_DS_DRA_MAIL_PROBLEM: The replication operation encountered an error with the mail system.")// ERROR_DS_DRA_MAIL_PROBLEM
        ERR(8448L, "ERROR_DS_DRA_REF_ALREADY_EXISTS: The replication reference information for the target server already exists.")// ERROR_DS_DRA_REF_ALREADY_EXISTS
        ERR(8449L, "ERROR_DS_DRA_REF_NOT_FOUND: The replication reference information for the target server does not exist.")// ERROR_DS_DRA_REF_NOT_FOUND
        ERR(8450L, "ERROR_DS_DRA_OBJ_IS_REP_SOURCE: The naming context cannot be removed because it is replicated to another server.")// ERROR_DS_DRA_OBJ_IS_REP_SOURCE
        ERR(8451L, "ERROR_DS_DRA_DB_ERROR: The replication operation encountered a database error.")// ERROR_DS_DRA_DB_ERROR
        ERR(8452L, "ERROR_DS_DRA_NO_REPLICA: The naming context is in the process of being removed or is not replicated from the specified server.")// ERROR_DS_DRA_NO_REPLICA
        ERR(8453L, "ERROR_DS_DRA_ACCESS_DENIED: Replication access was denied.")// ERROR_DS_DRA_ACCESS_DENIED
        ERR(8454L, "ERROR_DS_DRA_NOT_SUPPORTED: The requested operation is not supported by this version of the directory service.")// ERROR_DS_DRA_NOT_SUPPORTED
        ERR(8455L, "ERROR_DS_DRA_RPC_CANCELLED: The replication remote procedure call was cancelled.")// ERROR_DS_DRA_RPC_CANCELLED
        ERR(8456L, "ERROR_DS_DRA_SOURCE_DISABLED: The source server is currently rejecting replication requests.")// ERROR_DS_DRA_SOURCE_DISABLED
        ERR(8457L, "ERROR_DS_DRA_SINK_DISABLED: The destination server is currently rejecting replication requests.")// ERROR_DS_DRA_SINK_DISABLED
        ERR(8458L, "ERROR_DS_DRA_NAME_COLLISION: The replication operation failed due to a collision of object names.")// ERROR_DS_DRA_NAME_COLLISION
        ERR(8459L, "ERROR_DS_DRA_SOURCE_REINSTALLED: The replication source has been reinstalled.")// ERROR_DS_DRA_SOURCE_REINSTALLED
        ERR(8460L, "ERROR_DS_DRA_MISSING_PARENT: The replication operation failed because a required parent object is missing.")// ERROR_DS_DRA_MISSING_PARENT
        ERR(8461L, "ERROR_DS_DRA_PREEMPTED: The replication operation was preempted.")// ERROR_DS_DRA_PREEMPTED
        ERR(8462L, "ERROR_DS_DRA_ABANDON_SYNC: The replication synchronization attempt was abandoned because of a lack of updates.")// ERROR_DS_DRA_ABANDON_SYNC
        ERR(8463L, "ERROR_DS_DRA_SHUTDOWN: The replication operation was terminated because the system is shutting down.")// ERROR_DS_DRA_SHUTDOWN
        ERR(8464L, "ERROR_DS_DRA_INCOMPATIBLE_PARTIAL_SET: The replication synchronization attempt failed as the destination partial attribute set is not a subset of source partial attribute set.")// ERROR_DS_DRA_INCOMPATIBLE_PARTIAL_SET
        ERR(8465L, "ERROR_DS_DRA_SOURCE_IS_PARTIAL_REPLICA: The replication synchronization attempt failed because a master replica attempted to sync from a partial replica.")// ERROR_DS_DRA_SOURCE_IS_PARTIAL_REPLICA
        ERR(8466L, "ERROR_DS_DRA_EXTN_CONNECTION_FAILED: The server specified for this replication operation was contacted, but that server was unable to contact an additional server needed to complete the operation.")// ERROR_DS_DRA_EXTN_CONNECTION_FAILED
        ERR(8467L, "ERROR_DS_INSTALL_SCHEMA_MISMATCH: A schema mismatch is detected between the source and the build used during a replica install. The replica cannot be installed.")// ERROR_DS_INSTALL_SCHEMA_MISMATCH
        ERR(8468L, "ERROR_DS_DUP_LINK_ID: Schema update failed: An attribute with the same link identifier already exists.")// ERROR_DS_DUP_LINK_ID
        ERR(8469L, "ERROR_DS_NAME_ERROR_RESOLVING: Name translation: Generic processing error.")// ERROR_DS_NAME_ERROR_RESOLVING
        ERR(8470L, "ERROR_DS_NAME_ERROR_NOT_FOUND: Name translation: Could not find the name or insufficient right to see name.")// ERROR_DS_NAME_ERROR_NOT_FOUND
        ERR(8471L, "ERROR_DS_NAME_ERROR_NOT_UNIQUE: Name translation: Input name mapped to more than one output name.")// ERROR_DS_NAME_ERROR_NOT_UNIQUE
        ERR(8472L, "ERROR_DS_NAME_ERROR_NO_MAPPING: Name translation: Input name found, but not the associated output format.")// ERROR_DS_NAME_ERROR_NO_MAPPING
        ERR(8473L, "ERROR_DS_NAME_ERROR_DOMAIN_ONLY: Name translation: Unable to resolve completely, only the domain was found.")// ERROR_DS_NAME_ERROR_DOMAIN_ONLY
        ERR(8474L, "ERROR_DS_NAME_ERROR_NO_SYNTACTICAL_MAPPING: Name translation: Unable to perform purely syntactical mapping at the client without going out to the wire.")// ERROR_DS_NAME_ERROR_NO_SYNTACTICAL_MAPPING
        ERR(8475L, "ERROR_DS_CONSTRUCTED_ATT_MOD: Modification of a constructed att is not allowed.")// ERROR_DS_CONSTRUCTED_ATT_MOD
        ERR(8476L, "ERROR_DS_WRONG_OM_OBJ_CLASS: The OM-Object-Class specified is incorrect for an attribute with the specified syntax.")// ERROR_DS_WRONG_OM_OBJ_CLASS
        ERR(8477L, "ERROR_DS_DRA_REPL_PENDING: The replication request has been posted; waiting for reply.")// ERROR_DS_DRA_REPL_PENDING
        ERR(8478L, "ERROR_DS_DS_REQUIRED: The requested operation requires a directory service, and none was available.")// ERROR_DS_DS_REQUIRED
        ERR(8479L, "ERROR_DS_INVALID_LDAP_DISPLAY_NAME: The LDAP display name of the class or attribute contains non-ASCII characters.")// ERROR_DS_INVALID_LDAP_DISPLAY_NAME
        ERR(8480L, "ERROR_DS_NON_BASE_SEARCH: The requested search operation is only supported for base searches.")// ERROR_DS_NON_BASE_SEARCH
        ERR(8481L, "ERROR_DS_CANT_RETRIEVE_ATTS: The search failed to retrieve attributes from the database.")// ERROR_DS_CANT_RETRIEVE_ATTS
        ERR(8482L, "ERROR_DS_BACKLINK_WITHOUT_LINK: The schema update operation tried to add a backward link attribute that has no corresponding forward link.")// ERROR_DS_BACKLINK_WITHOUT_LINK
        ERR(8483L, "ERROR_DS_EPOCH_MISMATCH: Source and destination of a cross-domain move do not agree on the object's epoch number. Either source or destination does not have the latest version of the object.")// ERROR_DS_EPOCH_MISMATCH
        ERR(8484L, "ERROR_DS_SRC_NAME_MISMATCH: Source and destination of a cross-domain move do not agree on the object's current name. Either source or destination does not have the latest version of the object.")// ERROR_DS_SRC_NAME_MISMATCH
        ERR(8485L, "ERROR_DS_SRC_AND_DST_NC_IDENTICAL: Source and destination for the cross-domain move operation are identical. Caller should use local move operation instead of cross-domain move operation.")// ERROR_DS_SRC_AND_DST_NC_IDENTICAL
        ERR(8486L, "ERROR_DS_DST_NC_MISMATCH: Source and destination for a cross-domain move are not in agreement on the naming contexts in the forest. Either source or destination does not have the latest version of the Partitions container.")// ERROR_DS_DST_NC_MISMATCH
        ERR(8487L, "ERROR_DS_NOT_AUTHORITIVE_FOR_DST_NC: Destination of a cross-domain move is not authoritative for the destination naming context.")// ERROR_DS_NOT_AUTHORITIVE_FOR_DST_NC
        ERR(8488L, "ERROR_DS_SRC_GUID_MISMATCH: Source and destination of a cross-domain move do not agree on the identity of the source object. Either source or destination does not have the latest version of the source object.")// ERROR_DS_SRC_GUID_MISMATCH
        ERR(8489L, "ERROR_DS_CANT_MOVE_DELETED_OBJECT: Object being moved across-domains is already known to be deleted by the destination server. The source server does not have the latest version of the source object.")// ERROR_DS_CANT_MOVE_DELETED_OBJECT
        ERR(8490L, "ERROR_DS_PDC_OPERATION_IN_PROGRESS: Another operation which requires exclusive access to the PDC FSMO is already in progress.")// ERROR_DS_PDC_OPERATION_IN_PROGRESS
        ERR(8491L, "ERROR_DS_CROSS_DOMAIN_CLEANUP_REQD: A cross-domain move operation failed such that two versions of the moved object exist - one each in the source and destination domains. The destination object needs to be removed to restore the system to a consistent state.")// ERROR_DS_CROSS_DOMAIN_CLEANUP_REQD
        ERR(8492L, "ERROR_DS_ILLEGAL_XDOM_MOVE_OPERATION: This object may not be moved across domain boundaries either because cross-domain moves for this class are disallowed, or the object has some special characteristics, eg: trust account or restricted RID, which prevent its move.")// ERROR_DS_ILLEGAL_XDOM_MOVE_OPERATION
        ERR(8493L, "ERROR_DS_CANT_WITH_ACCT_GROUP_MEMBERSHPS: Can't move objects with memberships across domain boundaries as once moved, this would violate the membership conditions of the account group. Remove the object from any account group memberships and retry.")// ERROR_DS_CANT_WITH_ACCT_GROUP_MEMBERSHPS
        ERR(8494L, "ERROR_DS_NC_MUST_HAVE_NC_PARENT: A naming context head must be the immediate child of another naming context head, not of an interior node.")// ERROR_DS_NC_MUST_HAVE_NC_PARENT
        ERR(8495L, "ERROR_DS_CR_IMPOSSIBLE_TO_VALIDATE: The directory cannot validate the proposed naming context name because it does not hold a replica of the naming context above the proposed naming context. Please ensure that the domain naming master role is held by a server that is configured as a global catalog server, and that the server is up to date with its replication partners.")// ERROR_DS_CR_IMPOSSIBLE_TO_VALIDATE
        ERR(8496L, "ERROR_DS_DST_DOMAIN_NOT_NATIVE: Destination domain must be in native mode.")// ERROR_DS_DST_DOMAIN_NOT_NATIVE
        ERR(8497L, "ERROR_DS_MISSING_INFRASTRUCTURE_CONTAINER: The operation can not be performed because the server does not have an infrastructure container in the domain of interest.")// ERROR_DS_MISSING_INFRASTRUCTURE_CONTAINER
        ERR(8498L, "ERROR_DS_CANT_MOVE_ACCOUNT_GROUP: Cross-domain move of non-empty account groups is not allowed.")// ERROR_DS_CANT_MOVE_ACCOUNT_GROUP
        ERR(8499L, "ERROR_DS_CANT_MOVE_RESOURCE_GROUP: Cross-domain move of non-empty resource groups is not allowed.")// ERROR_DS_CANT_MOVE_RESOURCE_GROUP
        ERR(8500L, "ERROR_DS_INVALID_SEARCH_FLAG: The search flags for the attribute are invalid. The ANR bit is valid only on attributes of Unicode or Teletex strings.")// ERROR_DS_INVALID_SEARCH_FLAG
        ERR(8501L, "ERROR_DS_NO_TREE_DELETE_ABOVE_NC: Tree deletions starting at an object which has an NC head as a descendant are not allowed.")// ERROR_DS_NO_TREE_DELETE_ABOVE_NC
        ERR(8502L, "ERROR_DS_COULDNT_LOCK_TREE_FOR_DELETE: The directory service failed to lock a tree in preparation for a tree deletion because the tree was in use.")// ERROR_DS_COULDNT_LOCK_TREE_FOR_DELETE
        ERR(8503L, "ERROR_DS_COULDNT_IDENTIFY_OBJECTS_FOR_TREE_DELETE: The directory service failed to identify the list of objects to delete while attempting a tree deletion.")// ERROR_DS_COULDNT_IDENTIFY_OBJECTS_FOR_TREE_DELETE
        ERR(8504L, "ERROR_DS_SAM_INIT_FAILURE: Security Accounts Manager initialization failed because of the following error: %1.")// ERROR_DS_SAM_INIT_FAILURE
        ERR(8505L, "ERROR_DS_SENSITIVE_GROUP_VIOLATION: Only an administrator can modify the membership list of an administrative group.")// ERROR_DS_SENSITIVE_GROUP_VIOLATION
        ERR(8506L, "ERROR_DS_CANT_MOD_PRIMARYGROUPID: Cannot change the primary group ID of a domain controller account.")// ERROR_DS_CANT_MOD_PRIMARYGROUPID
        ERR(8507L, "ERROR_DS_ILLEGAL_BASE_SCHEMA_MOD: An attempt is made to modify the base schema.")// ERROR_DS_ILLEGAL_BASE_SCHEMA_MOD
        ERR(8508L, "ERROR_DS_NONSAFE_SCHEMA_CHANGE: Adding a new mandatory attribute to an existing class, deleting a mandatory attribute from an existing class, or adding an optional attribute to the special class Top that is not a backlink attribute (directly or through inheritance, for example, by adding or deleting an auxiliary class) is not allowed.")// ERROR_DS_NONSAFE_SCHEMA_CHANGE
        ERR(8509L, "ERROR_DS_SCHEMA_UPDATE_DISALLOWED: Schema update is not allowed on this DC because the DC is not the schema FSMO Role Owner.")// ERROR_DS_SCHEMA_UPDATE_DISALLOWED
        ERR(8510L, "ERROR_DS_CANT_CREATE_UNDER_SCHEMA: An object of this class cannot be created under the schema container. You can only create attribute-schema and class-schema objects under the schema container.")// ERROR_DS_CANT_CREATE_UNDER_SCHEMA
        ERR(8511L, "ERROR_DS_INSTALL_NO_SRC_SCH_VERSION: The replica/child install failed to get the objectVersion attribute on the schema container on the source DC. Either the attribute is missing on the schema container or the credentials supplied do not have permission to read it.")// ERROR_DS_INSTALL_NO_SRC_SCH_VERSION
        ERR(8512L, "ERROR_DS_INSTALL_NO_SCH_VERSION_IN_INIFILE: The replica/child install failed to read the objectVersion attribute in the SCHEMA section of the file schema.ini in the system32 directory.")// ERROR_DS_INSTALL_NO_SCH_VERSION_IN_INIFILE
        ERR(8513L, "ERROR_DS_INVALID_GROUP_TYPE: The specified group type is invalid.")// ERROR_DS_INVALID_GROUP_TYPE
        ERR(8514L, "ERROR_DS_NO_NEST_GLOBALGROUP_IN_MIXEDDOMAIN: You cannot nest global groups in a mixed domain if the group is security-enabled.")// ERROR_DS_NO_NEST_GLOBALGROUP_IN_MIXEDDOMAIN
        ERR(8515L, "ERROR_DS_NO_NEST_LOCALGROUP_IN_MIXEDDOMAIN: You cannot nest local groups in a mixed domain if the group is security-enabled.")// ERROR_DS_NO_NEST_LOCALGROUP_IN_MIXEDDOMAIN
        ERR(8516L, "ERROR_DS_GLOBAL_CANT_HAVE_LOCAL_MEMBER: A global group cannot have a local group as a member.")// ERROR_DS_GLOBAL_CANT_HAVE_LOCAL_MEMBER
        ERR(8517L, "ERROR_DS_GLOBAL_CANT_HAVE_UNIVERSAL_MEMBER: A global group cannot have a universal group as a member.")// ERROR_DS_GLOBAL_CANT_HAVE_UNIVERSAL_MEMBER
        ERR(8518L, "ERROR_DS_UNIVERSAL_CANT_HAVE_LOCAL_MEMBER: A universal group cannot have a local group as a member.")// ERROR_DS_UNIVERSAL_CANT_HAVE_LOCAL_MEMBER
        ERR(8519L, "ERROR_DS_GLOBAL_CANT_HAVE_CROSSDOMAIN_MEMBER: A global group cannot have a cross-domain member.")// ERROR_DS_GLOBAL_CANT_HAVE_CROSSDOMAIN_MEMBER
        ERR(8520L, "ERROR_DS_LOCAL_CANT_HAVE_CROSSDOMAIN_LOCAL_MEMBER: A local group cannot have another cross domain local group as a member.")// ERROR_DS_LOCAL_CANT_HAVE_CROSSDOMAIN_LOCAL_MEMBER
        ERR(8521L, "ERROR_DS_HAVE_PRIMARY_MEMBERS: A group with primary members cannot change to a security-disabled group.")// ERROR_DS_HAVE_PRIMARY_MEMBERS
        ERR(8522L, "ERROR_DS_STRING_SD_CONVERSION_FAILED: The schema cache load failed to convert the string default SD on a class-schema object.")// ERROR_DS_STRING_SD_CONVERSION_FAILED
        ERR(8523L, "ERROR_DS_NAMING_MASTER_GC: Only DSAs configured to be Global Catalog servers should be allowed to hold the Domain Naming Master FSMO role.")// ERROR_DS_NAMING_MASTER_GC
        ERR(8524L, "ERROR_DS_DNS_LOOKUP_FAILURE: The DSA operation is unable to proceed because of a DNS lookup failure.")// ERROR_DS_DNS_LOOKUP_FAILURE
        ERR(8525L, "ERROR_DS_COULDNT_UPDATE_SPNS: While processing a change to the DNS Host Name for an object, the Service Principal Name values could not be kept in sync.")// ERROR_DS_COULDNT_UPDATE_SPNS
        ERR(8526L, "ERROR_DS_CANT_RETRIEVE_SD: The Security Descriptor attribute could not be read.")// ERROR_DS_CANT_RETRIEVE_SD
        ERR(8527L, "ERROR_DS_KEY_NOT_UNIQUE: The object requested was not found, but an object with that key was found.")// ERROR_DS_KEY_NOT_UNIQUE
        ERR(8528L, "ERROR_DS_WRONG_LINKED_ATT_SYNTAX: The syntax of the linked attribute being added is incorrect. Forward links can only have syntax 2.5.5.1, 2.5.5.7, and 2.5.5.14, and backlinks can only have syntax 2.5.5.1")// ERROR_DS_WRONG_LINKED_ATT_SYNTAX
        ERR(8529L, "ERROR_DS_SAM_NEED_BOOTKEY_PASSWORD: Security Account Manager needs to get the boot password.")// ERROR_DS_SAM_NEED_BOOTKEY_PASSWORD
        ERR(8530L, "ERROR_DS_SAM_NEED_BOOTKEY_FLOPPY: Security Account Manager needs to get the boot key from floppy disk.")// ERROR_DS_SAM_NEED_BOOTKEY_FLOPPY
        ERR(8531L, "ERROR_DS_CANT_START: Directory Service cannot start.")// ERROR_DS_CANT_START
        ERR(8532L, "ERROR_DS_INIT_FAILURE: Directory Services could not start.")// ERROR_DS_INIT_FAILURE
        ERR(8533L, "ERROR_DS_NO_PKT_PRIVACY_ON_CONNECTION: The connection between client and server requires packet privacy or better.")// ERROR_DS_NO_PKT_PRIVACY_ON_CONNECTION
        ERR(8534L, "ERROR_DS_SOURCE_DOMAIN_IN_FOREST: The source domain may not be in the same forest as destination.")// ERROR_DS_SOURCE_DOMAIN_IN_FOREST
        ERR(8535L, "ERROR_DS_DESTINATION_DOMAIN_NOT_IN_FOREST: The destination domain must be in the forest.")// ERROR_DS_DESTINATION_DOMAIN_NOT_IN_FOREST
        ERR(8536L, "ERROR_DS_DESTINATION_AUDITING_NOT_ENABLED: The operation requires that destination domain auditing be enabled.")// ERROR_DS_DESTINATION_AUDITING_NOT_ENABLED
        ERR(8537L, "ERROR_DS_CANT_FIND_DC_FOR_SRC_DOMAIN: The operation couldn't locate a DC for the source domain.")// ERROR_DS_CANT_FIND_DC_FOR_SRC_DOMAIN
        ERR(8538L, "ERROR_DS_SRC_OBJ_NOT_GROUP_OR_USER: The source object must be a group or user.")// ERROR_DS_SRC_OBJ_NOT_GROUP_OR_USER
        ERR(8539L, "ERROR_DS_SRC_SID_EXISTS_IN_FOREST: The source object's SID already exists in destination forest.")// ERROR_DS_SRC_SID_EXISTS_IN_FOREST
        ERR(8540L, "ERROR_DS_SRC_AND_DST_OBJECT_CLASS_MISMATCH: The source and destination object must be of the same type.")// ERROR_DS_SRC_AND_DST_OBJECT_CLASS_MISMATCH
        ERR(8541L, "ERROR_SAM_INIT_FAILURE: Security Accounts Manager initialization failed because of the following error: %1.")// ERROR_SAM_INIT_FAILURE
        ERR(8542L, "ERROR_DS_DRA_SCHEMA_INFO_SHIP: Schema information could not be included in the replication request.")// ERROR_DS_DRA_SCHEMA_INFO_SHIP
        ERR(8543L, "ERROR_DS_DRA_SCHEMA_CONFLICT: The replication operation could not be completed due to a schema")// ERROR_DS_DRA_SCHEMA_CONFLICT
        ERR(8544L, "ERROR_DS_DRA_EARLIER_SCHEMA_CONFLICT: The replication operation could not be completed due to a previous schema incompatibility.")// ERROR_DS_DRA_EARLIER_SCHEMA_CONFLICT
        ERR(8545L, "ERROR_DS_DRA_OBJ_NC_MISMATCH: The replication update could not be applied because either the source or the destination has not yet received information regarding a recent cross-domain move operation.")// ERROR_DS_DRA_OBJ_NC_MISMATCH
        ERR(8546L, "ERROR_DS_NC_STILL_HAS_DSAS: The requested domain could not be deleted because there exist domain controllers that still host this domain.")// ERROR_DS_NC_STILL_HAS_DSAS
        ERR(8547L, "ERROR_DS_GC_REQUIRED: The requested operation can be performed only on a global catalog server.")// ERROR_DS_GC_REQUIRED
        ERR(8548L, "ERROR_DS_LOCAL_MEMBER_OF_LOCAL_ONLY: A local group can only be a member of other local groups in the same domain.")// ERROR_DS_LOCAL_MEMBER_OF_LOCAL_ONLY
        ERR(8549L, "ERROR_DS_NO_FPO_IN_UNIVERSAL_GROUPS: Foreign security principals cannot be members of universal groups.")// ERROR_DS_NO_FPO_IN_UNIVERSAL_GROUPS
        ERR(8550L, "ERROR_DS_CANT_ADD_TO_GC: The attribute is not allowed to be replicated to the GC because of security reasons.")// ERROR_DS_CANT_ADD_TO_GC
        ERR(8551L, "ERROR_DS_NO_CHECKPOINT_WITH_PDC: The checkpoint with the PDC could not be taken because there too many modifications being processed currently.")// ERROR_DS_NO_CHECKPOINT_WITH_PDC
        ERR(8552L, "ERROR_DS_SOURCE_AUDITING_NOT_ENABLED: The operation requires that source domain auditing be enabled.")// ERROR_DS_SOURCE_AUDITING_NOT_ENABLED
        ERR(8553L, "ERROR_DS_CANT_CREATE_IN_NONDOMAIN_NC: Security principal objects can only be created inside domain naming contexts.")// ERROR_DS_CANT_CREATE_IN_NONDOMAIN_NC
        ERR(8554L, "ERROR_DS_INVALID_NAME_FOR_SPN: A Service Principal Name (SPN) could not be constructed because the provided hostname is not in the necessary format.")// ERROR_DS_INVALID_NAME_FOR_SPN
        ERR(8555L, "ERROR_DS_FILTER_USES_CONTRUCTED_ATTRS: A Filter was passed that uses constructed attributes.")// ERROR_DS_FILTER_USES_CONTRUCTED_ATTRS
        ERR(8556L, "ERROR_DS_UNICODEPWD_NOT_IN_QUOTES: The unicodePwd attribute value must be enclosed in double quotes.")// ERROR_DS_UNICODEPWD_NOT_IN_QUOTES
        ERR(8557L, "ERROR_DS_MACHINE_ACCOUNT_QUOTA_EXCEEDED: Your computer could not be joined to the domain. You have exceeded the maximum number of computer accounts you are allowed to create in this domain. Contact your system administrator to have this limit reset or increased.")// ERROR_DS_MACHINE_ACCOUNT_QUOTA_EXCEEDED
        ERR(8558L, "ERROR_DS_MUST_BE_RUN_ON_DST_DC: For security reasons, the operation must be run on the destination DC.")// ERROR_DS_MUST_BE_RUN_ON_DST_DC
        ERR(8559L, "ERROR_DS_SRC_DC_MUST_BE_SP4_OR_GREATER: For security reasons, the source DC must be NT4SP4 or greater.")// ERROR_DS_SRC_DC_MUST_BE_SP4_OR_GREATER
        ERR(8560L, "ERROR_DS_CANT_TREE_DELETE_CRITICAL_OBJ: Critical Directory Service System objects cannot be deleted during tree delete operations. The tree delete may have been partially performed.")// ERROR_DS_CANT_TREE_DELETE_CRITICAL_OBJ
        ERR(8561L, "ERROR_DS_INIT_FAILURE_CONSOLE: Directory Services could not start because of the following error: %1.")// ERROR_DS_INIT_FAILURE_CONSOLE
        ERR(8562L, "ERROR_DS_SAM_INIT_FAILURE_CONSOLE: Security Accounts Manager initialization failed because of the following error: %1.")// ERROR_DS_SAM_INIT_FAILURE_CONSOLE
        ERR(8563L, "ERROR_DS_FOREST_VERSION_TOO_HIGH: This version of Windows is too old to support the current directory forest behavior. You must upgrade the operating system on this server before it can become a domain controller in this forest.")// ERROR_DS_FOREST_VERSION_TOO_HIGH
        ERR(8564L, "ERROR_DS_DOMAIN_VERSION_TOO_HIGH: This version of Windows is too old to support the current domain behavior. You must upgrade the operating system on this server before it can become a domain controller in this domain.")// ERROR_DS_DOMAIN_VERSION_TOO_HIGH
        ERR(8565L, "ERROR_DS_FOREST_VERSION_TOO_LOW: This version of Windows no longer supports the behavior version in use in this directory forest. You must advance the forest behavior version before this server can become a domain controller in the forest. ")// ERROR_DS_FOREST_VERSION_TOO_LOW
        ERR(8566L, "ERROR_DS_DOMAIN_VERSION_TOO_LOW: This version of Windows no longer supports the behavior version in use in this domain. You must advance the domain behavior version before this server can become a domain controller in the domain. ")// ERROR_DS_DOMAIN_VERSION_TOO_LOW
        ERR(8567L, "ERROR_DS_INCOMPATIBLE_VERSION: The version of Windows is incompatible with the behavior version of the domain or forest.")// ERROR_DS_INCOMPATIBLE_VERSION
        ERR(8568L, "ERROR_DS_LOW_DSA_VERSION: The behavior version cannot be increased to the requested value because Domain Controllers still exist with versions lower than the requested value.")// ERROR_DS_LOW_DSA_VERSION
        ERR(8569L, "ERROR_DS_NO_BEHAVIOR_VERSION_IN_MIXEDDOMAIN: The behavior version value cannot be increased while the domain is still in mixed domain mode. You must first change the domain to native mode before increasing the behavior version.")// ERROR_DS_NO_BEHAVIOR_VERSION_IN_MIXEDDOMAIN
        ERR(8570L, "ERROR_DS_NOT_SUPPORTED_SORT_ORDER: The sort order requested is not supported.")// ERROR_DS_NOT_SUPPORTED_SORT_ORDER
        ERR(8571L, "ERROR_DS_NAME_NOT_UNIQUE: Found an object with a non unique name.")// ERROR_DS_NAME_NOT_UNIQUE
        ERR(8572L, "ERROR_DS_MACHINE_ACCOUNT_CREATED_PRENT4: The machine account was created pre-NT4. The account needs to be recreated.")// ERROR_DS_MACHINE_ACCOUNT_CREATED_PRENT4
        ERR(8573L, "ERROR_DS_OUT_OF_VERSION_STORE: The database is out of version store.")// ERROR_DS_OUT_OF_VERSION_STORE
        ERR(8574L, "ERROR_DS_INCOMPATIBLE_CONTROLS_USED: Unable to continue operation because multiple conflicting controls were used.")// ERROR_DS_INCOMPATIBLE_CONTROLS_USED
        ERR(8575L, "ERROR_DS_NO_REF_DOMAIN: Unable to find a valid security descriptor reference domain for this partition.")// ERROR_DS_NO_REF_DOMAIN
        ERR(8576L, "ERROR_DS_RESERVED_LINK_ID: Schema update failed: The link identifier is reserved.")// ERROR_DS_RESERVED_LINK_ID
        ERR(8577L, "ERROR_DS_LINK_ID_NOT_AVAILABLE: Schema update failed: There are no link identifiers available.")// ERROR_DS_LINK_ID_NOT_AVAILABLE
        ERR(9001L, "DNS_ERROR_RCODE_FORMAT_ERROR: DNS server unable to interpret format.")// DNS_ERROR_RCODE_FORMAT_ERROR
        ERR(9002L, "DNS_ERROR_RCODE_SERVER_FAILURE: DNS server failure.")// DNS_ERROR_RCODE_SERVER_FAILURE
        ERR(9003L, "DNS_ERROR_RCODE_NAME_ERROR: DNS name does not exist.")// DNS_ERROR_RCODE_NAME_ERROR
        ERR(9004L, "DNS_ERROR_RCODE_NOT_IMPLEMENTED: DNS request not supported by name server.")// DNS_ERROR_RCODE_NOT_IMPLEMENTED
        ERR(9005L, "DNS_ERROR_RCODE_REFUSED: DNS operation refused.")// DNS_ERROR_RCODE_REFUSED
        ERR(9006L, "DNS_ERROR_RCODE_YXDOMAIN: DNS name that ought not exist, does exist.")// DNS_ERROR_RCODE_YXDOMAIN
        ERR(9007L, "DNS_ERROR_RCODE_YXRRSET: DNS RR set that ought not exist, does exist.")// DNS_ERROR_RCODE_YXRRSET
        ERR(9008L, "DNS_ERROR_RCODE_NXRRSET: DNS RR set that ought to exist, does not exist.")// DNS_ERROR_RCODE_NXRRSET
        ERR(9009L, "DNS_ERROR_RCODE_NOTAUTH: DNS server not authoritative for zone.")// DNS_ERROR_RCODE_NOTAUTH
        ERR(9010L, "DNS_ERROR_RCODE_NOTZONE: DNS name in update or prereq is not in zone.")// DNS_ERROR_RCODE_NOTZONE
        ERR(9016L, "DNS_ERROR_RCODE_BADSIG: DNS signature failed to verify.")// DNS_ERROR_RCODE_BADSIG
        ERR(9017L, "DNS_ERROR_RCODE_BADKEY: DNS bad key.")// DNS_ERROR_RCODE_BADKEY
        ERR(9018L, "DNS_ERROR_RCODE_BADTIME: DNS signature validity expired.")// DNS_ERROR_RCODE_BADTIME
        ERR(9501L, "DNS_INFO_NO_RECORDS: No records found for given DNS query.")// DNS_INFO_NO_RECORDS
        ERR(9502L, "DNS_ERROR_BAD_PACKET: Bad DNS packet.")// DNS_ERROR_BAD_PACKET
        ERR(9503L, "DNS_ERROR_NO_PACKET: No DNS packet.")// DNS_ERROR_NO_PACKET
        ERR(9504L, "DNS_ERROR_RCODE: DNS error, check rcode.")// DNS_ERROR_RCODE
        ERR(9505L, "DNS_ERROR_UNSECURE_PACKET: Unsecured DNS packet.")// DNS_ERROR_UNSECURE_PACKET
        ERR(9551L, "DNS_ERROR_INVALID_TYPE: Invalid DNS type.")// DNS_ERROR_INVALID_TYPE
        ERR(9552L, "DNS_ERROR_INVALID_IP_ADDRESS: Invalid IP address.")// DNS_ERROR_INVALID_IP_ADDRESS
        ERR(9553L, "DNS_ERROR_INVALID_PROPERTY: Invalid property.")// DNS_ERROR_INVALID_PROPERTY
        ERR(9554L, "DNS_ERROR_TRY_AGAIN_LATER: Try DNS operation again later.")// DNS_ERROR_TRY_AGAIN_LATER
        ERR(9555L, "DNS_ERROR_NOT_UNIQUE: Record for given name and type is not unique.")// DNS_ERROR_NOT_UNIQUE
        ERR(9556L, "DNS_ERROR_NON_RFC_NAME: DNS name does not comply with RFC specifications.")// DNS_ERROR_NON_RFC_NAME
        ERR(9557L, "DNS_STATUS_FQDN: DNS name is a fully-qualified DNS name.")// DNS_STATUS_FQDN
        ERR(9558L, "DNS_STATUS_DOTTED_NAME: DNS name is dotted (multi-label).")// DNS_STATUS_DOTTED_NAME
        ERR(9559L, "DNS_STATUS_SINGLE_PART_NAME: DNS name is a single-part name.")// DNS_STATUS_SINGLE_PART_NAME
        ERR(9560L, "DNS_ERROR_INVALID_NAME_CHAR: DNS name contains an invalid character.")// DNS_ERROR_INVALID_NAME_CHAR
        ERR(9561L, "DNS_ERROR_NUMERIC_NAME: DNS name is entirely numeric.")// DNS_ERROR_NUMERIC_NAME
        ERR(9601L, "DNS_ERROR_ZONE_DOES_NOT_EXIST: DNS zone does not exist.")// DNS_ERROR_ZONE_DOES_NOT_EXIST
        ERR(9602L, "DNS_ERROR_NO_ZONE_INFO: DNS zone information not available.")// DNS_ERROR_NO_ZONE_INFO
        ERR(9603L, "DNS_ERROR_INVALID_ZONE_OPERATION: Invalid operation for DNS zone.")// DNS_ERROR_INVALID_ZONE_OPERATION
        ERR(9604L, "DNS_ERROR_ZONE_CONFIGURATION_ERROR: Invalid DNS zone configuration.")// DNS_ERROR_ZONE_CONFIGURATION_ERROR
        ERR(9605L, "DNS_ERROR_ZONE_HAS_NO_SOA_RECORD: DNS zone has no start of authority (SOA) record.")// DNS_ERROR_ZONE_HAS_NO_SOA_RECORD
        ERR(9606L, "DNS_ERROR_ZONE_HAS_NO_NS_RECORDS: DNS zone has no Name Server (NS) record.")// DNS_ERROR_ZONE_HAS_NO_NS_RECORDS
        ERR(9607L, "DNS_ERROR_ZONE_LOCKED: DNS zone is locked.")// DNS_ERROR_ZONE_LOCKED
        ERR(9608L, "DNS_ERROR_ZONE_CREATION_FAILED: DNS zone creation failed.")// DNS_ERROR_ZONE_CREATION_FAILED
        ERR(9609L, "DNS_ERROR_ZONE_ALREADY_EXISTS: DNS zone already exists.")// DNS_ERROR_ZONE_ALREADY_EXISTS
        ERR(9610L, "DNS_ERROR_AUTOZONE_ALREADY_EXISTS: DNS automatic zone already exists.")// DNS_ERROR_AUTOZONE_ALREADY_EXISTS
        ERR(9611L, "DNS_ERROR_INVALID_ZONE_TYPE: Invalid DNS zone type.")// DNS_ERROR_INVALID_ZONE_TYPE
        ERR(9612L, "DNS_ERROR_SECONDARY_REQUIRES_MASTER_IP: Secondary DNS zone requires master IP address.")// DNS_ERROR_SECONDARY_REQUIRES_MASTER_IP
        ERR(9613L, "DNS_ERROR_ZONE_NOT_SECONDARY: DNS zone not secondary.")// DNS_ERROR_ZONE_NOT_SECONDARY
        ERR(9614L, "DNS_ERROR_NEED_SECONDARY_ADDRESSES: Need secondary IP address.")// DNS_ERROR_NEED_SECONDARY_ADDRESSES
        ERR(9615L, "DNS_ERROR_WINS_INIT_FAILED: WINS initialization failed.")// DNS_ERROR_WINS_INIT_FAILED
        ERR(9616L, "DNS_ERROR_NEED_WINS_SERVERS: Need WINS servers.")// DNS_ERROR_NEED_WINS_SERVERS
        ERR(9617L, "DNS_ERROR_NBSTAT_INIT_FAILED: NBTSTAT initialization call failed.")// DNS_ERROR_NBSTAT_INIT_FAILED
        ERR(9618L, "DNS_ERROR_SOA_DELETE_INVALID: Invalid delete of start of authority (SOA)")// DNS_ERROR_SOA_DELETE_INVALID
        ERR(9651L, "DNS_ERROR_PRIMARY_REQUIRES_DATAFILE: Primary DNS zone requires datafile.")// DNS_ERROR_PRIMARY_REQUIRES_DATAFILE
        ERR(9652L, "DNS_ERROR_INVALID_DATAFILE_NAME: Invalid datafile name for DNS zone.")// DNS_ERROR_INVALID_DATAFILE_NAME
        ERR(9653L, "DNS_ERROR_DATAFILE_OPEN_FAILURE: Failed to open datafile for DNS zone.")// DNS_ERROR_DATAFILE_OPEN_FAILURE
        ERR(9654L, "DNS_ERROR_FILE_WRITEBACK_FAILED: Failed to write datafile for DNS zone.")// DNS_ERROR_FILE_WRITEBACK_FAILED
        ERR(9655L, "DNS_ERROR_DATAFILE_PARSING: Failure while reading datafile for DNS zone.")// DNS_ERROR_DATAFILE_PARSING
        ERR(9701L, "DNS_ERROR_RECORD_DOES_NOT_EXIST: DNS record does not exist.")// DNS_ERROR_RECORD_DOES_NOT_EXIST
        ERR(9702L, "DNS_ERROR_RECORD_FORMAT: DNS record format error.")// DNS_ERROR_RECORD_FORMAT
        ERR(9703L, "DNS_ERROR_NODE_CREATION_FAILED: Node creation failure in DNS.")// DNS_ERROR_NODE_CREATION_FAILED
        ERR(9704L, "DNS_ERROR_UNKNOWN_RECORD_TYPE: Unknown DNS record type.")// DNS_ERROR_UNKNOWN_RECORD_TYPE
        ERR(9705L, "DNS_ERROR_RECORD_TIMED_OUT: DNS record timed out.")// DNS_ERROR_RECORD_TIMED_OUT
        ERR(9706L, "DNS_ERROR_NAME_NOT_IN_ZONE: Name not in DNS zone.")// DNS_ERROR_NAME_NOT_IN_ZONE
        ERR(9707L, "DNS_ERROR_CNAME_LOOP: CNAME loop detected.")// DNS_ERROR_CNAME_LOOP
        ERR(9708L, "DNS_ERROR_NODE_IS_CNAME: Node is a CNAME DNS record.")// DNS_ERROR_NODE_IS_CNAME
        ERR(9709L, "DNS_ERROR_CNAME_COLLISION: A CNAME record already exists for given name.")// DNS_ERROR_CNAME_COLLISION
        ERR(9710L, "DNS_ERROR_RECORD_ONLY_AT_ZONE_ROOT: Record only at DNS zone root.")// DNS_ERROR_RECORD_ONLY_AT_ZONE_ROOT
        ERR(9711L, "DNS_ERROR_RECORD_ALREADY_EXISTS: DNS record already exists.")// DNS_ERROR_RECORD_ALREADY_EXISTS
        ERR(9712L, "DNS_ERROR_SECONDARY_DATA: Secondary DNS zone data error.")// DNS_ERROR_SECONDARY_DATA
        ERR(9713L, "DNS_ERROR_NO_CREATE_CACHE_DATA: Could not create DNS cache data.")// DNS_ERROR_NO_CREATE_CACHE_DATA
        ERR(9714L, "DNS_ERROR_NAME_DOES_NOT_EXIST: DNS name does not exist.")// DNS_ERROR_NAME_DOES_NOT_EXIST
        ERR(9715L, "DNS_WARNING_PTR_CREATE_FAILED: Could not create pointer (PTR) record.")// DNS_WARNING_PTR_CREATE_FAILED
        ERR(9716L, "DNS_WARNING_DOMAIN_UNDELETED: DNS domain was undeleted.")// DNS_WARNING_DOMAIN_UNDELETED
        ERR(9717L, "DNS_ERROR_DS_UNAVAILABLE: The directory service is unavailable.")// DNS_ERROR_DS_UNAVAILABLE
        ERR(9718L, "DNS_ERROR_DS_ZONE_ALREADY_EXISTS: DNS zone already exists in the directory service.")// DNS_ERROR_DS_ZONE_ALREADY_EXISTS
        ERR(9719L, "DNS_ERROR_NO_BOOTFILE_IF_DS_ZONE: DNS server not creating or reading the boot file for the directory service integrated DNS zone.")// DNS_ERROR_NO_BOOTFILE_IF_DS_ZONE
        ERR(9751L, "DNS_INFO_AXFR_COMPLETE: DNS AXFR (zone transfer) complete.")// DNS_INFO_AXFR_COMPLETE
        ERR(9752L, "DNS_ERROR_AXFR: DNS zone transfer failed.")// DNS_ERROR_AXFR
        ERR(9753L, "DNS_INFO_ADDED_LOCAL_WINS: Added local WINS server.")// DNS_INFO_ADDED_LOCAL_WINS
        ERR(9801L, "DNS_STATUS_CONTINUE_NEEDED: Secure update call needs to continue update request.")// DNS_STATUS_CONTINUE_NEEDED
        ERR(9851L, "DNS_ERROR_NO_TCPIP: TCP/IP network protocol not installed.")// DNS_ERROR_NO_TCPIP
        ERR(9852L, "DNS_ERROR_NO_DNS_SERVERS: No DNS servers configured for local system.")// DNS_ERROR_NO_DNS_SERVERS
        ERR(10004L, "WSAEINTR: A blocking operation was interrupted by a call to WSACancelBlockingCall.")// WSAEINTR
        ERR(10009L, "WSAEBADF: The file handle supplied is not valid.")// WSAEBADF
        ERR(10013L, "WSAEACCES: An attempt was made to access a socket in a way forbidden by its access permissions.")// WSAEACCES
        ERR(10014L, "WSAEFAULT: The system detected an invalid pointer address in attempting to use a pointer argument in a call.")// WSAEFAULT
        ERR(10022L, "WSAEINVAL: An invalid argument was supplied.")// WSAEINVAL
        ERR(10024L, "WSAEMFILE: Too many open sockets.")// WSAEMFILE
        ERR(10035L, "WSAEWOULDBLOCK: A non-blocking socket operation could not be completed immediately.")// WSAEWOULDBLOCK
        ERR(10036L, "WSAEINPROGRESS: A blocking operation is currently executing.")// WSAEINPROGRESS
        ERR(10037L, "WSAEALREADY: An operation was attempted on a non-blocking socket that already had an operation in progress.")// WSAEALREADY
        ERR(10038L, "WSAENOTSOCK: An operation was attempted on something that is not a socket.")// WSAENOTSOCK
        ERR(10039L, "WSAEDESTADDRREQ: A required address was omitted from an operation on a socket.")// WSAEDESTADDRREQ
        ERR(10040L, "WSAEMSGSIZE: A message sent on a datagram socket was larger than the internal message buffer or some other network limit, or the buffer used to receive a datagram into was smaller than the datagram itself.")// WSAEMSGSIZE
        ERR(10041L, "WSAEPROTOTYPE: A protocol was specified in the socket function call that does not support the semantics of the socket type requested.")// WSAEPROTOTYPE
        ERR(10042L, "WSAENOPROTOOPT: An unknown, invalid, or unsupported option or level was specified in a getsockopt or setsockopt call.")// WSAENOPROTOOPT
        ERR(10043L, "WSAEPROTONOSUPPORT: The requested protocol has not been configured into the system, or no implementation for it exists.")// WSAEPROTONOSUPPORT
        ERR(10044L, "WSAESOCKTNOSUPPORT: The support for the specified socket type does not exist in this address family.")// WSAESOCKTNOSUPPORT
        ERR(10045L, "WSAEOPNOTSUPP: The attempted operation is not supported for the type of object referenced.")// WSAEOPNOTSUPP
        ERR(10046L, "WSAEPFNOSUPPORT: The protocol family has not been configured into the system or no implementation for it exists.")// WSAEPFNOSUPPORT
        ERR(10047L, "WSAEAFNOSUPPORT: An address incompatible with the requested protocol was used.")// WSAEAFNOSUPPORT
        ERR(10048L, "WSAEADDRINUSE: Only one usage of each socket address (protocol/network address/port)")// WSAEADDRINUSE
        ERR(10049L, "WSAEADDRNOTAVAIL: The requested address is not valid in its context.")// WSAEADDRNOTAVAIL
        ERR(10050L, "WSAENETDOWN: A socket operation encountered a dead network.")// WSAENETDOWN
        ERR(10051L, "WSAENETUNREACH: A socket operation was attempted to an unreachable network.")// WSAENETUNREACH
        ERR(10052L, "WSAENETRESET: The connection has been broken due to keep-alive activity detecting a failure while the operation was in progress.")// WSAENETRESET
        ERR(10053L, "WSAECONNABORTED: An established connection was aborted by the software in your host machine.")// WSAECONNABORTED
        ERR(10054L, "WSAECONNRESET: An existing connection was forcibly closed by the remote host.")// WSAECONNRESET
        ERR(10055L, "WSAENOBUFS: An operation on a socket could not be performed because the system lacked sufficient buffer space or because a queue was full.")// WSAENOBUFS
        ERR(10056L, "WSAEISCONN: A connect request was made on an already connected socket.")// WSAEISCONN
        ERR(10057L, "WSAENOTCONN: A request to send or receive data was disallowed because the socket is not connected and (when sending on a datagram socket using a sendto call) no address was supplied.")// WSAENOTCONN
        ERR(10058L, "WSAESHUTDOWN: A request to send or receive data was disallowed because the socket had already been shut down in that direction with a previous shutdown call.")// WSAESHUTDOWN
        ERR(10059L, "WSAETOOMANYREFS: Too many references to some kernel object.")// WSAETOOMANYREFS
        ERR(10060L, "WSAETIMEDOUT: A connection attempt failed because the connected party did not properly respond after a period of time, or established connection failed because connected host has failed to respond.")// WSAETIMEDOUT
        ERR(10061L, "WSAECONNREFUSED: No connection could be made because the target machine actively refused it.")// WSAECONNREFUSED
        ERR(10062L, "WSAELOOP: Cannot translate name.")// WSAELOOP
        ERR(10063L, "WSAENAMETOOLONG: Name component or name was too long.")// WSAENAMETOOLONG
        ERR(10064L, "WSAEHOSTDOWN: A socket operation failed because the destination host was down.")// WSAEHOSTDOWN
        ERR(10065L, "WSAEHOSTUNREACH: A socket operation was attempted to an unreachable host.")// WSAEHOSTUNREACH
        ERR(10066L, "WSAENOTEMPTY: Cannot remove a directory that is not empty.")// WSAENOTEMPTY
        ERR(10067L, "WSAEPROCLIM: A Windows Sockets implementation may have a limit on the number of applications that may use it simultaneously.")// WSAEPROCLIM
        ERR(10068L, "WSAEUSERS: Ran out of quota.")// WSAEUSERS
        ERR(10069L, "WSAEDQUOT: Ran out of disk quota.")// WSAEDQUOT
        ERR(10070L, "WSAESTALE: File handle reference is no longer available.")// WSAESTALE
        ERR(10071L, "WSAEREMOTE: Item is not available locally.")// WSAEREMOTE
        ERR(10091L, "WSASYSNOTREADY: WSAStartup cannot function at this time because the underlying system it uses to provide network services is currently unavailable.")// WSASYSNOTREADY
        ERR(10092L, "WSAVERNOTSUPPORTED: The Windows Sockets version requested is not supported.")// WSAVERNOTSUPPORTED
        ERR(10093L, "WSANOTINITIALISED: Either the application has not called WSAStartup, or WSAStartup failed.")// WSANOTINITIALISED
        ERR(10101L, "WSAEDISCON: Returned by WSARecv or WSARecvFrom to indicate the remote party has initiated a graceful shutdown sequence.")// WSAEDISCON
        ERR(10102L, "WSAENOMORE: No more results can be returned by WSALookupServiceNext.")// WSAENOMORE
        ERR(10103L, "WSAECANCELLED: A call to WSALookupServiceEnd was made while this call was still processing. The call has been canceled.")// WSAECANCELLED
        ERR(10104L, "WSAEINVALIDPROCTABLE: The procedure call table is invalid.")// WSAEINVALIDPROCTABLE
        ERR(10105L, "WSAEINVALIDPROVIDER: The requested service provider is invalid.")// WSAEINVALIDPROVIDER
        ERR(10106L, "WSAEPROVIDERFAILEDINIT: The requested service provider could not be loaded or initialized.")// WSAEPROVIDERFAILEDINIT
        ERR(10107L, "WSASYSCALLFAILURE: A system call that should never fail has failed.")// WSASYSCALLFAILURE
        ERR(10108L, "WSASERVICE_NOT_FOUND: No such service is known. The service cannot be found in the specified name space.")// WSASERVICE_NOT_FOUND
        ERR(10109L, "WSATYPE_NOT_FOUND: The specified class was not found.")// WSATYPE_NOT_FOUND
        ERR(10110L, "WSA_E_NO_MORE: No more results can be returned by WSALookupServiceNext.")// WSA_E_NO_MORE
        ERR(10111L, "WSA_E_CANCELLED: A call to WSALookupServiceEnd was made while this call was still processing. The call has been canceled.")// WSA_E_CANCELLED
        ERR(10112L, "WSAEREFUSED: A database query failed because it was actively refused.")// WSAEREFUSED
        ERR(11001L, "WSAHOST_NOT_FOUND: No such host is known.")// WSAHOST_NOT_FOUND
        ERR(11002L, "WSATRY_AGAIN: This is usually a temporary error during hostname resolution and means that the local server did not receive a response from an authoritative server.")// WSATRY_AGAIN
        ERR(11003L, "WSANO_RECOVERY: A non-recoverable error occurred during a database lookup.")// WSANO_RECOVERY
        ERR(11004L, "WSANO_DATA: The requested name is valid and was found in the database, but it does not have the correct associated data being resolved for.")// WSANO_DATA
        ERR(11005L, "WSA_QOS_RECEIVERS: At least one reserve has arrived.")// WSA_QOS_RECEIVERS
        ERR(11006L, "WSA_QOS_SENDERS: At least one path has arrived.")// WSA_QOS_SENDERS
        ERR(11007L, "WSA_QOS_NO_SENDERS: There are no senders.")// WSA_QOS_NO_SENDERS
        ERR(11008L, "WSA_QOS_NO_RECEIVERS: There are no receivers.")// WSA_QOS_NO_RECEIVERS
        ERR(11009L, "WSA_QOS_REQUEST_CONFIRMED: Reserve has been confirmed.")// WSA_QOS_REQUEST_CONFIRMED
        ERR(11010L, "WSA_QOS_ADMISSION_FAILURE: Error due to lack of resources.")// WSA_QOS_ADMISSION_FAILURE
        ERR(11011L, "WSA_QOS_POLICY_FAILURE: Rejected for administrative reasons - bad credentials.")// WSA_QOS_POLICY_FAILURE
        ERR(11012L, "WSA_QOS_BAD_STYLE: Unknown or conflicting style.")// WSA_QOS_BAD_STYLE
        ERR(11013L, "WSA_QOS_BAD_OBJECT: Problem with some part of the filterspec or providerspecific buffer in general.")// WSA_QOS_BAD_OBJECT
        ERR(11014L, "WSA_QOS_TRAFFIC_CTRL_ERROR: Problem with some part of the flowspec.")// WSA_QOS_TRAFFIC_CTRL_ERROR
        ERR(11015L, "WSA_QOS_GENERIC_ERROR: General QOS error.")// WSA_QOS_GENERIC_ERROR
        ERR(11016L, "WSA_QOS_ESERVICETYPE: An invalid or unrecognized service type was found in the flowspec.")// WSA_QOS_ESERVICETYPE
        ERR(11017L, "WSA_QOS_EFLOWSPEC: An invalid or inconsistent flowspec was found in the QOS structure.")// WSA_QOS_EFLOWSPEC
        ERR(11018L, "WSA_QOS_EPROVSPECBUF: Invalid QOS provider-specific buffer.")// WSA_QOS_EPROVSPECBUF
        ERR(11019L, "WSA_QOS_EFILTERSTYLE: An invalid QOS filter style was used.")// WSA_QOS_EFILTERSTYLE
        ERR(11020L, "WSA_QOS_EFILTERTYPE: An invalid QOS filter type was used.")// WSA_QOS_EFILTERTYPE
        ERR(11021L, "WSA_QOS_EFILTERCOUNT: An incorrect number of QOS FILTERSPECs were specified in the FLOWDESCRIPTOR.")// WSA_QOS_EFILTERCOUNT
        ERR(11022L, "WSA_QOS_EOBJLENGTH: An object with an invalid ObjectLength field was specified in the QOS provider-specific buffer.")// WSA_QOS_EOBJLENGTH
        ERR(11023L, "WSA_QOS_EFLOWCOUNT: An incorrect number of flow descriptors was specified in the QOS structure.")// WSA_QOS_EFLOWCOUNT
        ERR(11024L, "WSA_QOS_EUNKOWNPSOBJ: An unrecognized object was found in the QOS provider-specific buffer.")// WSA_QOS_EUNKOWNPSOBJ
        ERR(11025L, "WSA_QOS_EPOLICYOBJ: An invalid policy object was found in the QOS provider-specific buffer.")// WSA_QOS_EPOLICYOBJ
        ERR(11026L, "WSA_QOS_EFLOWDESC: An invalid QOS flow descriptor was found in the flow descriptor list.")// WSA_QOS_EFLOWDESC
        ERR(11027L, "WSA_QOS_EPSFLOWSPEC: An invalid or inconsistent flowspec was found in the QOS provider specific buffer.")// WSA_QOS_EPSFLOWSPEC
        ERR(11028L, "WSA_QOS_EPSFILTERSPEC: An invalid FILTERSPEC was found in the QOS provider-specific buffer.")// WSA_QOS_EPSFILTERSPEC
        ERR(11029L, "WSA_QOS_ESDMODEOBJ: An invalid shape discard mode object was found in the QOS provider specific buffer.")// WSA_QOS_ESDMODEOBJ
        ERR(11030L, "WSA_QOS_ESHAPERATEOBJ: An invalid shaping rate object was found in the QOS provider-specific buffer.")// WSA_QOS_ESHAPERATEOBJ
        ERR(11031L, "WSA_QOS_RESERVED_PETYPE: A reserved policy element was found in the QOS provider-specific buffer.")// WSA_QOS_RESERVED_PETYPE
        ERR(12000L, "ERROR_SXS_SECTION_NOT_FOUND: The requested section was not present in the activation context.")// ERROR_SXS_SECTION_NOT_FOUND
        ERR(12001L, "ERROR_SXS_CANT_GEN_ACTCTX: Windows was not able to process the application binding information.")// ERROR_SXS_CANT_GEN_ACTCTX
        ERR(12002L, "ERROR_SXS_INVALID_ACTCTXDATA_FORMAT: The application binding data format is invalid.")// ERROR_SXS_INVALID_ACTCTXDATA_FORMAT
        ERR(12003L, "ERROR_SXS_ASSEMBLY_NOT_FOUND: The referenced assembly is not installed on your system.")// ERROR_SXS_ASSEMBLY_NOT_FOUND
        ERR(12004L, "ERROR_SXS_MANIFEST_FORMAT_ERROR: The manifest file does not begin with the required tag and format information.")// ERROR_SXS_MANIFEST_FORMAT_ERROR
        ERR(12005L, "ERROR_SXS_MANIFEST_PARSE_ERROR: The manifest file contains one or more syntax errors.")// ERROR_SXS_MANIFEST_PARSE_ERROR
        ERR(12006L, "ERROR_SXS_ACTIVATION_CONTEXT_DISABLED: The application attempted to activate a disabled activation context.")// ERROR_SXS_ACTIVATION_CONTEXT_DISABLED
        ERR(12007L, "ERROR_SXS_KEY_NOT_FOUND: The requested lookup key was not found in any active activation context.")// ERROR_SXS_KEY_NOT_FOUND
        ERR(12008L, "ERROR_SXS_VERSION_CONFLICT: A component version required by the application conflicts with another component version already active.")// ERROR_SXS_VERSION_CONFLICT
        ERR(12009L, "ERROR_SXS_WRONG_SECTION_TYPE: The type requested activation context section does not match the query API used.")// ERROR_SXS_WRONG_SECTION_TYPE
        ERR(12010L, "ERROR_SXS_THREAD_QUERIES_DISABLED: Lack of system resources has required isolated activation to be disabled for the current thread of execution.")// ERROR_SXS_THREAD_QUERIES_DISABLED
        ERR(13000L, "ERROR_IPSEC_QM_POLICY_EXISTS: The specified quick mode policy already exists.")// ERROR_IPSEC_QM_POLICY_EXISTS
        ERR(13001L, "ERROR_IPSEC_QM_POLICY_NOT_FOUND: The specified quick mode policy was not found.")// ERROR_IPSEC_QM_POLICY_NOT_FOUND
        ERR(13002L, "ERROR_IPSEC_QM_POLICY_IN_USE: The specified quick mode policy is being used.")// ERROR_IPSEC_QM_POLICY_IN_USE
        ERR(13003L, "ERROR_IPSEC_MM_POLICY_EXISTS: The specified main mode policy already exists.")// ERROR_IPSEC_MM_POLICY_EXISTS
        ERR(13004L, "ERROR_IPSEC_MM_POLICY_NOT_FOUND: The specified main mode policy was not found")// ERROR_IPSEC_MM_POLICY_NOT_FOUND
        ERR(13005L, "ERROR_IPSEC_MM_POLICY_IN_USE: The specified main mode policy is being used.")// ERROR_IPSEC_MM_POLICY_IN_USE
        ERR(13006L, "ERROR_IPSEC_MM_FILTER_EXISTS: The specified main mode filter already exists.")// ERROR_IPSEC_MM_FILTER_EXISTS
        ERR(13007L, "ERROR_IPSEC_MM_FILTER_NOT_FOUND: The specified main mode filter was not found.")// ERROR_IPSEC_MM_FILTER_NOT_FOUND
        ERR(13008L, "ERROR_IPSEC_TRANSPORT_FILTER_EXISTS: The specified transport mode filter already exists.")// ERROR_IPSEC_TRANSPORT_FILTER_EXISTS
        ERR(13009L, "ERROR_IPSEC_TRANSPORT_FILTER_NOT_FOUND: The specified transport mode filter does not exist.")// ERROR_IPSEC_TRANSPORT_FILTER_NOT_FOUND
        ERR(13010L, "ERROR_IPSEC_MM_AUTH_EXISTS: The specified main mode authentication list exists.")// ERROR_IPSEC_MM_AUTH_EXISTS
        ERR(13011L, "ERROR_IPSEC_MM_AUTH_NOT_FOUND: The specified main mode authentication list was not found.")// ERROR_IPSEC_MM_AUTH_NOT_FOUND
        ERR(13012L, "ERROR_IPSEC_MM_AUTH_IN_USE: The specified quick mode policy is being used.")// ERROR_IPSEC_MM_AUTH_IN_USE
        ERR(13013L, "ERROR_IPSEC_DEFAULT_MM_POLICY_NOT_FOUND: The specified main mode policy already exists.")// ERROR_IPSEC_DEFAULT_MM_POLICY_NOT_FOUND
        ERR(13014L, "ERROR_IPSEC_DEFAULT_MM_AUTH_NOT_FOUND: The specified quick mode policy was not found")// ERROR_IPSEC_DEFAULT_MM_AUTH_NOT_FOUND
        ERR(13015L, "ERROR_IPSEC_DEFAULT_QM_POLICY_NOT_FOUND: The manifest file contains one or more syntax errors.")// ERROR_IPSEC_DEFAULT_QM_POLICY_NOT_FOUND
        ERR(13016L, "ERROR_IPSEC_TUNNEL_FILTER_EXISTS: The application attempted to activate a disabled activation context.")// ERROR_IPSEC_TUNNEL_FILTER_EXISTS
        ERR(13017L, "ERROR_IPSEC_TUNNEL_FILTER_NOT_FOUND: The requested lookup key was not found in any active activation context.")// ERROR_IPSEC_TUNNEL_FILTER_NOT_FOUND
        ERR(13018L, "ERROR_IPSEC_MM_FILTER_PENDING_DELETION: The Main Mode filter is pending deletion.")// ERROR_IPSEC_MM_FILTER_PENDING_DELETION
        ERR(13019L, "ERROR_IPSEC_TRANSPORT_FILTER_PENDING_DELETION: The transport filter is pending deletion.")// ERROR_IPSEC_TRANSPORT_FILTER_PENDING_DELETION
        ERR(13020L, "ERROR_IPSEC_TUNNEL_FILTER_PENDING_DELETION: The tunnel filter is pending deletion.")// ERROR_IPSEC_TUNNEL_FILTER_PENDING_DELETION
        ERR(13021L, "ERROR_IPSEC_MM_POLICY_PENDING_DELETION: The Main Mode policy is pending deletion.")// ERROR_IPSEC_MM_POLICY_PENDING_DELETION
        ERR(13022L, "ERROR_IPSEC_MM_AUTH_PENDING_DELETION: The Main Mode authentication bundle is pending deletion.")// ERROR_IPSEC_MM_AUTH_PENDING_DELETION
        ERR(13023L, "ERROR_IPSEC_QM_POLICY_PENDING_DELETION: The Quick Mode policy is pending deletion.")// ERROR_IPSEC_QM_POLICY_PENDING_DELETION
        ERR(13800L, "ERROR_IPSEC_IKE_NEG_STATUS_BEGIN: ERROR_IPSEC_IKE_NEG_STATUS_BEGIN")// ERROR_IPSEC_IKE_NEG_STATUS_BEGIN
        ERR(13801L, "ERROR_IPSEC_IKE_AUTH_FAIL: IKE authentication credentials are unacceptable")// ERROR_IPSEC_IKE_AUTH_FAIL
        ERR(13802L, "ERROR_IPSEC_IKE_ATTRIB_FAIL: IKE security attributes are unacceptable")// ERROR_IPSEC_IKE_ATTRIB_FAIL
        ERR(13803L, "ERROR_IPSEC_IKE_NEGOTIATION_PENDING: IKE Negotiation in progress")// ERROR_IPSEC_IKE_NEGOTIATION_PENDING
        ERR(13804L, "ERROR_IPSEC_IKE_GENERAL_PROCESSING_ERROR: General processing error")// ERROR_IPSEC_IKE_GENERAL_PROCESSING_ERROR
        ERR(13805L, "ERROR_IPSEC_IKE_TIMED_OUT: Negotiation timed out")// ERROR_IPSEC_IKE_TIMED_OUT
        ERR(13806L, "ERROR_IPSEC_IKE_NO_CERT: IKE failed to find valid machine certificate")// ERROR_IPSEC_IKE_NO_CERT
        ERR(13807L, "ERROR_IPSEC_IKE_SA_DELETED: IKE SA deleted by peer before establishment completed")// ERROR_IPSEC_IKE_SA_DELETED
        ERR(13808L, "ERROR_IPSEC_IKE_SA_REAPED: IKE SA deleted before establishment completed")// ERROR_IPSEC_IKE_SA_REAPED
        ERR(13809L, "ERROR_IPSEC_IKE_MM_ACQUIRE_DROP: Negotiation request sat in Queue too long")// ERROR_IPSEC_IKE_MM_ACQUIRE_DROP
        ERR(13810L, "ERROR_IPSEC_IKE_QM_ACQUIRE_DROP: Negotiation request sat in Queue too long")// ERROR_IPSEC_IKE_QM_ACQUIRE_DROP
        ERR(13811L, "ERROR_IPSEC_IKE_QUEUE_DROP_MM: Negotiation request sat in Queue too long")// ERROR_IPSEC_IKE_QUEUE_DROP_MM
        ERR(13812L, "ERROR_IPSEC_IKE_QUEUE_DROP_NO_MM: Negotiation request sat in Queue too long")// ERROR_IPSEC_IKE_QUEUE_DROP_NO_MM
        ERR(13813L, "ERROR_IPSEC_IKE_DROP_NO_RESPONSE: No response from peer")// ERROR_IPSEC_IKE_DROP_NO_RESPONSE
        ERR(13814L, "ERROR_IPSEC_IKE_MM_DELAY_DROP: Negotiation took too long")// ERROR_IPSEC_IKE_MM_DELAY_DROP
        ERR(13815L, "ERROR_IPSEC_IKE_QM_DELAY_DROP: Negotiation took too long")// ERROR_IPSEC_IKE_QM_DELAY_DROP
        ERR(13816L, "ERROR_IPSEC_IKE_ERROR: Unknown error occurred")// ERROR_IPSEC_IKE_ERROR
        ERR(13817L, "ERROR_IPSEC_IKE_CRL_FAILED: Certificate Revocation Check failed")// ERROR_IPSEC_IKE_CRL_FAILED
        ERR(13818L, "ERROR_IPSEC_IKE_INVALID_KEY_USAGE: Invalid certificate key usage")// ERROR_IPSEC_IKE_INVALID_KEY_USAGE
        ERR(13819L, "ERROR_IPSEC_IKE_INVALID_CERT_TYPE: Invalid certificate type")// ERROR_IPSEC_IKE_INVALID_CERT_TYPE
        ERR(13820L, "ERROR_IPSEC_IKE_NO_PRIVATE_KEY: No private key associated with machine certificate")// ERROR_IPSEC_IKE_NO_PRIVATE_KEY
        ERR(13822L, "ERROR_IPSEC_IKE_DH_FAIL: Failure in Diffie-Helman computation")// ERROR_IPSEC_IKE_DH_FAIL
        ERR(13824L, "ERROR_IPSEC_IKE_INVALID_HEADER: Invalid header")// ERROR_IPSEC_IKE_INVALID_HEADER
        ERR(13825L, "ERROR_IPSEC_IKE_NO_POLICY: No policy configured")// ERROR_IPSEC_IKE_NO_POLICY
        ERR(13826L, "ERROR_IPSEC_IKE_INVALID_SIGNATURE: Failed to verify signature")// ERROR_IPSEC_IKE_INVALID_SIGNATURE
        ERR(13827L, "ERROR_IPSEC_IKE_KERBEROS_ERROR: Failed to authenticate using kerberos")// ERROR_IPSEC_IKE_KERBEROS_ERROR
        ERR(13828L, "ERROR_IPSEC_IKE_NO_PUBLIC_KEY: Peer's certificate did not have a public key")// ERROR_IPSEC_IKE_NO_PUBLIC_KEY
        ERR(13829L, "ERROR_IPSEC_IKE_PROCESS_ERR: Error processing error payload")// ERROR_IPSEC_IKE_PROCESS_ERR
        ERR(13830L, "ERROR_IPSEC_IKE_PROCESS_ERR_SA: Error processing SA payload")// ERROR_IPSEC_IKE_PROCESS_ERR_SA
        ERR(13831L, "ERROR_IPSEC_IKE_PROCESS_ERR_PROP: Error processing Proposal payload")// ERROR_IPSEC_IKE_PROCESS_ERR_PROP
        ERR(13832L, "ERROR_IPSEC_IKE_PROCESS_ERR_TRANS: Error processing Transform payload")// ERROR_IPSEC_IKE_PROCESS_ERR_TRANS
        ERR(13833L, "ERROR_IPSEC_IKE_PROCESS_ERR_KE: Error processing KE payload")// ERROR_IPSEC_IKE_PROCESS_ERR_KE
        ERR(13834L, "ERROR_IPSEC_IKE_PROCESS_ERR_ID: Error processing ID payload")// ERROR_IPSEC_IKE_PROCESS_ERR_ID
        ERR(13835L, "ERROR_IPSEC_IKE_PROCESS_ERR_CERT: Error processing Cert payload")// ERROR_IPSEC_IKE_PROCESS_ERR_CERT
        ERR(13836L, "ERROR_IPSEC_IKE_PROCESS_ERR_CERT_REQ: Error processing Certificate Request payload")// ERROR_IPSEC_IKE_PROCESS_ERR_CERT_REQ
        ERR(13837L, "ERROR_IPSEC_IKE_PROCESS_ERR_HASH: Error processing Hash payload")// ERROR_IPSEC_IKE_PROCESS_ERR_HASH
        ERR(13838L, "ERROR_IPSEC_IKE_PROCESS_ERR_SIG: Error processing Signature payload")// ERROR_IPSEC_IKE_PROCESS_ERR_SIG
        ERR(13839L, "ERROR_IPSEC_IKE_PROCESS_ERR_NONCE: Error processing Nonce payload")// ERROR_IPSEC_IKE_PROCESS_ERR_NONCE
        ERR(13840L, "ERROR_IPSEC_IKE_PROCESS_ERR_NOTIFY: Error processing Notify payload")// ERROR_IPSEC_IKE_PROCESS_ERR_NOTIFY
        ERR(13841L, "ERROR_IPSEC_IKE_PROCESS_ERR_DELETE: Error processing Delete Payload")// ERROR_IPSEC_IKE_PROCESS_ERR_DELETE
        ERR(13842L, "ERROR_IPSEC_IKE_PROCESS_ERR_VENDOR: Error processing VendorId payload")// ERROR_IPSEC_IKE_PROCESS_ERR_VENDOR
        ERR(13843L, "ERROR_IPSEC_IKE_INVALID_PAYLOAD: Invalid payload received")// ERROR_IPSEC_IKE_INVALID_PAYLOAD
        ERR(13844L, "ERROR_IPSEC_IKE_LOAD_SOFT_SA: Soft SA loaded")// ERROR_IPSEC_IKE_LOAD_SOFT_SA
        ERR(13845L, "ERROR_IPSEC_IKE_SOFT_SA_TORN_DOWN: Soft SA torn down")// ERROR_IPSEC_IKE_SOFT_SA_TORN_DOWN
        ERR(13846L, "ERROR_IPSEC_IKE_INVALID_COOKIE: Invalid cookie received.")// ERROR_IPSEC_IKE_INVALID_COOKIE
        ERR(13847L, "ERROR_IPSEC_IKE_NO_PEER_CERT: Peer failed to send valid machine certificate")// ERROR_IPSEC_IKE_NO_PEER_CERT
        ERR(13848L, "ERROR_IPSEC_IKE_PEER_CRL_FAILED: Certification Revocation check of peer's certificate failed")// ERROR_IPSEC_IKE_PEER_CRL_FAILED
        ERR(13849L, "ERROR_IPSEC_IKE_POLICY_CHANGE: New policy invalidated SAs formed with old policy")// ERROR_IPSEC_IKE_POLICY_CHANGE
        ERR(13850L, "ERROR_IPSEC_IKE_NO_MM_POLICY: There is no available Main Mode IKE policy. ")// ERROR_IPSEC_IKE_NO_MM_POLICY
        ERR(13851L, "ERROR_IPSEC_IKE_NOTCBPRIV: Failed to enabled TCB privilege.")// ERROR_IPSEC_IKE_NOTCBPRIV
        ERR(13852L, "ERROR_IPSEC_IKE_SECLOADFAIL: Failed to load SECURITY.DLL.")// ERROR_IPSEC_IKE_SECLOADFAIL
        ERR(13853L, "ERROR_IPSEC_IKE_FAILSSPINIT: Failed to obtain security function table dispatch address from SSPI.")// ERROR_IPSEC_IKE_FAILSSPINIT
        ERR(13854L, "ERROR_IPSEC_IKE_FAILQUERYSSP: Failed to query Kerberos package to obtain max token size.")// ERROR_IPSEC_IKE_FAILQUERYSSP
        ERR(13855L, "ERROR_IPSEC_IKE_SRVACQFAIL: Failed to obtain Kerberos server credentials for ISAKMP/ERROR_IPSEC_IKE service. Kerberos authentication will not function. The most likely reason for this is lack of domain membership. This is normal if your computer is a member of a workgroup.")// ERROR_IPSEC_IKE_SRVACQFAIL
        ERR(13856L, "ERROR_IPSEC_IKE_SRVQUERYCRED: Failed to determine SSPI principal name for ISAKMP/ERROR_IPSEC_IKE service (QueryCredentialsAttributes).")// ERROR_IPSEC_IKE_SRVQUERYCRED
        ERR(13857L, "ERROR_IPSEC_IKE_GETSPIFAIL: Failed to obtain new SPI for the inbound SA from Ipsec driver. The most common cause for this is that the driver does not have the correct filter. Check your policy to verify the filters.")// ERROR_IPSEC_IKE_GETSPIFAIL
        ERR(13858L, "ERROR_IPSEC_IKE_INVALID_FILTER: Given filter is invalid")// ERROR_IPSEC_IKE_INVALID_FILTER
        ERR(13859L, "ERROR_IPSEC_IKE_OUT_OF_MEMORY: Memory allocation failed. ")// ERROR_IPSEC_IKE_OUT_OF_MEMORY
        ERR(13860L, "ERROR_IPSEC_IKE_ADD_UPDATE_KEY_FAILED: Failed to add Security Association to IPSec Driver. The most common cause for this is if the IKE negotiation took too long to complete. If the problem persists, reduce the load on the faulting machine.")// ERROR_IPSEC_IKE_ADD_UPDATE_KEY_FAILED
        ERR(13861L, "ERROR_IPSEC_IKE_INVALID_POLICY: Invalid policy")// ERROR_IPSEC_IKE_INVALID_POLICY
        ERR(13862L, "ERROR_IPSEC_IKE_UNKNOWN_DOI: Invalid DOI")// ERROR_IPSEC_IKE_UNKNOWN_DOI
        ERR(13863L, "ERROR_IPSEC_IKE_INVALID_SITUATION: Invalid situation")// ERROR_IPSEC_IKE_INVALID_SITUATION
        ERR(13864L, "ERROR_IPSEC_IKE_DH_FAILURE: Diffie-Hellman failure")// ERROR_IPSEC_IKE_DH_FAILURE
        ERR(13865L, "ERROR_IPSEC_IKE_INVALID_GROUP: Invalid Diffie-Hellman group")// ERROR_IPSEC_IKE_INVALID_GROUP
        ERR(13866L, "ERROR_IPSEC_IKE_ENCRYPT: Error encrypting payload")// ERROR_IPSEC_IKE_ENCRYPT
        ERR(13867L, "ERROR_IPSEC_IKE_DECRYPT: Error decrypting payload")// ERROR_IPSEC_IKE_DECRYPT
        ERR(13868L, "ERROR_IPSEC_IKE_POLICY_MATCH: Policy match error")// ERROR_IPSEC_IKE_POLICY_MATCH
        ERR(13869L, "ERROR_IPSEC_IKE_UNSUPPORTED_ID: Unsupported ID")// ERROR_IPSEC_IKE_UNSUPPORTED_ID
        ERR(13870L, "ERROR_IPSEC_IKE_INVALID_HASH: Hash verification failed")// ERROR_IPSEC_IKE_INVALID_HASH
        ERR(13871L, "ERROR_IPSEC_IKE_INVALID_HASH_ALG: Invalid hash algorithm")// ERROR_IPSEC_IKE_INVALID_HASH_ALG
        ERR(13872L, "ERROR_IPSEC_IKE_INVALID_HASH_SIZE: Invalid hash size ")// ERROR_IPSEC_IKE_INVALID_HASH_SIZE
        ERR(13873L, "ERROR_IPSEC_IKE_INVALID_ENCRYPT_ALG: Invalid encryption algorithm")// ERROR_IPSEC_IKE_INVALID_ENCRYPT_ALG
        ERR(13874L, "ERROR_IPSEC_IKE_INVALID_AUTH_ALG: Invalid authentication algorithm")// ERROR_IPSEC_IKE_INVALID_AUTH_ALG
        ERR(13875L, "ERROR_IPSEC_IKE_INVALID_SIG: Invalid certificate signature")// ERROR_IPSEC_IKE_INVALID_SIG
        ERR(13876L, "ERROR_IPSEC_IKE_LOAD_FAILED: Load failed")// ERROR_IPSEC_IKE_LOAD_FAILED
        ERR(13877L, "ERROR_IPSEC_IKE_RPC_DELETE: Deleted via RPC call")// ERROR_IPSEC_IKE_RPC_DELETE
        ERR(13878L, "ERROR_IPSEC_IKE_BENIGN_REINIT: Temporary state created to perform reinit. This is not a real failure.")// ERROR_IPSEC_IKE_BENIGN_REINIT
        ERR(13879L, "ERROR_IPSEC_IKE_INVALID_RESPONDER_LIFETIME_NOTIFY: The lifetime value received in the Responder Lifetime Notify is below the Windows 2000 configured minimum value. Please fix the policy on the peer machine.")// ERROR_IPSEC_IKE_INVALID_RESPONDER_LIFETIME_NOTIFY
        ERR(13880L, "ERROR_IPSEC_IKE_QM_LIMIT_REAP: SA reaped because QM limit was reached")// ERROR_IPSEC_IKE_QM_LIMIT_REAP
        ERR(13881L, "ERROR_IPSEC_IKE_INVALID_CERT_KEYLEN: Key length in certificate is too small for configured security requirements.")// ERROR_IPSEC_IKE_INVALID_CERT_KEYLEN
        ERR(13882L, "ERROR_IPSEC_IKE_MM_LIMIT: Max number of established MM SAs to peer exceeded.")// ERROR_IPSEC_IKE_MM_LIMIT
        ERR(13883L, "ERROR_IPSEC_IKE_NEG_STATUS_END: ERROR_IPSEC_IKE_NEG_STATUS_END")// ERROR_IPSEC_IKE_NEG_STATUS_END
        ERR(0x8000FFFFL, "E_UNEXPECTED: Catastrophic failure")// E_UNEXPECTED
        ERR(0x80004001L, "E_NOTIMPL: Not implemented")// E_NOTIMPL
        ERR(0x8007000EL, "E_OUTOFMEMORY: Ran out of memory")// E_OUTOFMEMORY
        ERR(0x80070057L, "E_INVALIDARG: One or more arguments are invalid")// E_INVALIDARG
        ERR(0x80004002L, "E_NOINTERFACE: No such interface supported")// E_NOINTERFACE
        ERR(0x80004003L, "E_POINTER: Invalid pointer")// E_POINTER
        ERR(0x80070006L, "E_HANDLE: Invalid handle")// E_HANDLE
        ERR(0x80004004L, "E_ABORT: Operation aborted")// E_ABORT
        ERR(0x80004005L, "E_FAIL: Unspecified error")// E_FAIL
        ERR(0x80070005L, "E_ACCESSDENIED: General access denied error")// E_ACCESSDENIED
        ERR(0x80000001L, "E_NOTIMPL: Not implemented")// E_NOTIMPL
        ERR(0x80000002L, "E_OUTOFMEMORY: Ran out of memory")// E_OUTOFMEMORY
        ERR(0x80000003L, "E_INVALIDARG: One or more arguments are invalid")// E_INVALIDARG
        ERR(0x80000004L, "E_NOINTERFACE: No such interface supported")// E_NOINTERFACE
        ERR(0x80000005L, "E_POINTER: Invalid pointer")// E_POINTER
        ERR(0x80000006L, "E_HANDLE: Invalid handle")// E_HANDLE
        ERR(0x80000007L, "E_ABORT: Operation aborted")// E_ABORT
        ERR(0x80000008L, "E_FAIL: Unspecified error")// E_FAIL
        ERR(0x80000009L, "E_ACCESSDENIED: General access denied error")// E_ACCESSDENIED
        ERR(0x8000000AL, "E_PENDING: The data necessary to complete this operation is not yet available.")// E_PENDING
        ERR(0x80004006L, "CO_E_INIT_TLS: Thread local storage failure")// CO_E_INIT_TLS
        ERR(0x80004007L, "CO_E_INIT_SHARED_ALLOCATOR: Get shared memory allocator failure")// CO_E_INIT_SHARED_ALLOCATOR
        ERR(0x80004008L, "CO_E_INIT_MEMORY_ALLOCATOR: Get memory allocator failure")// CO_E_INIT_MEMORY_ALLOCATOR
        ERR(0x80004009L, "CO_E_INIT_CLASS_CACHE: Unable to initialize class cache")// CO_E_INIT_CLASS_CACHE
        ERR(0x8000400AL, "CO_E_INIT_RPC_CHANNEL: Unable to initialize RPC services")// CO_E_INIT_RPC_CHANNEL
        ERR(0x8000400BL, "CO_E_INIT_TLS_SET_CHANNEL_CONTROL: Cannot set thread local storage channel control")// CO_E_INIT_TLS_SET_CHANNEL_CONTROL
        ERR(0x8000400CL, "CO_E_INIT_TLS_CHANNEL_CONTROL: Could not allocate thread local storage channel control")// CO_E_INIT_TLS_CHANNEL_CONTROL
        ERR(0x8000400DL, "CO_E_INIT_UNACCEPTED_USER_ALLOCATOR: The user supplied memory allocator is unacceptable")// CO_E_INIT_UNACCEPTED_USER_ALLOCATOR
        ERR(0x8000400EL, "CO_E_INIT_SCM_MUTEX_EXISTS: The OLE service mutex already exists")// CO_E_INIT_SCM_MUTEX_EXISTS
        ERR(0x8000400FL, "CO_E_INIT_SCM_FILE_MAPPING_EXISTS: The OLE service file mapping already exists")// CO_E_INIT_SCM_FILE_MAPPING_EXISTS
        ERR(0x80004010L, "CO_E_INIT_SCM_MAP_VIEW_OF_FILE: Unable to map view of file for OLE service")// CO_E_INIT_SCM_MAP_VIEW_OF_FILE
        ERR(0x80004011L, "CO_E_INIT_SCM_EXEC_FAILURE: Failure attempting to launch OLE service")// CO_E_INIT_SCM_EXEC_FAILURE
        ERR(0x80004012L, "CO_E_INIT_ONLY_SINGLE_THREADED: There was an attempt to call CoInitialize a second time while single threaded")// CO_E_INIT_ONLY_SINGLE_THREADED
        ERR(0x80004013L, "CO_E_CANT_REMOTE: A Remote activation was necessary but was not allowed")// CO_E_CANT_REMOTE
        ERR(0x80004014L, "CO_E_BAD_SERVER_NAME: A Remote activation was necessary but the server name provided was invalid")// CO_E_BAD_SERVER_NAME
        ERR(0x80004015L, "CO_E_WRONG_SERVER_IDENTITY: The class is configured to run as a security id different from the caller")// CO_E_WRONG_SERVER_IDENTITY
        ERR(0x80004016L, "CO_E_OLE1DDE_DISABLED: Use of Ole1 services requiring DDE windows is disabled")// CO_E_OLE1DDE_DISABLED
        ERR(0x80004017L, "CO_E_RUNAS_SYNTAX: A RunAs specification must be <domain name>\\<user name> or simply <user name>")// CO_E_RUNAS_SYNTAX
        ERR(0x80004018L, "CO_E_CREATEPROCESS_FAILURE: The server process could not be started. The pathname may be incorrect.")// CO_E_CREATEPROCESS_FAILURE
        ERR(0x80004019L, "CO_E_RUNAS_CREATEPROCESS_FAILURE: The server process could not be started as the configured identity. The pathname may be incorrect or unavailable.")// CO_E_RUNAS_CREATEPROCESS_FAILURE
        ERR(0x8000401AL, "CO_E_RUNAS_LOGON_FAILURE: The server process could not be started because the configured identity is incorrect. Check the username and password.")// CO_E_RUNAS_LOGON_FAILURE
        ERR(0x8000401BL, "CO_E_LAUNCH_PERMSSION_DENIED: The client is not allowed to launch this server.")// CO_E_LAUNCH_PERMSSION_DENIED
        ERR(0x8000401CL, "CO_E_START_SERVICE_FAILURE: The service providing this server could not be started.")// CO_E_START_SERVICE_FAILURE
        ERR(0x8000401DL, "CO_E_REMOTE_COMMUNICATION_FAILURE: This computer was unable to communicate with the computer providing the server.")// CO_E_REMOTE_COMMUNICATION_FAILURE
        ERR(0x8000401EL, "CO_E_SERVER_START_TIMEOUT: The server did not respond after being launched.")// CO_E_SERVER_START_TIMEOUT
        ERR(0x8000401FL, "CO_E_CLSREG_INCONSISTENT: The registration information for this server is inconsistent or incomplete.")// CO_E_CLSREG_INCONSISTENT
        ERR(0x80004020L, "CO_E_IIDREG_INCONSISTENT: The registration information for this interface is inconsistent or incomplete.")// CO_E_IIDREG_INCONSISTENT
        ERR(0x80004021L, "CO_E_NOT_SUPPORTED: The operation attempted is not supported.")// CO_E_NOT_SUPPORTED
        ERR(0x80004022L, "CO_E_RELOAD_DLL: A dll must be loaded.")// CO_E_RELOAD_DLL
        ERR(0x80004023L, "CO_E_MSI_ERROR: A Microsoft Software Installer error was encountered.")// CO_E_MSI_ERROR
        ERR(0x80004024L, "CO_E_ATTEMPT_TO_CREATE_OUTSIDE_CLIENT_CONTEXT: The specified activation could not occur in the client context as specified.")// CO_E_ATTEMPT_TO_CREATE_OUTSIDE_CLIENT_CONTEXT
        ERR(0x80004025L, "CO_E_SERVER_PAUSED: Activations on the server are paused.")// CO_E_SERVER_PAUSED
        ERR(0x80004026L, "CO_E_SERVER_NOT_PAUSED: Activations on the server are not paused.")// CO_E_SERVER_NOT_PAUSED
        ERR(0x80004027L, "CO_E_CLASS_DISABLED: The component has been disabled.")// CO_E_CLASS_DISABLED
        ERR(0x80004028L, "CO_E_APPLICATION_DISABLED: The application has been disabled.")// CO_E_APPLICATION_DISABLED
        ERR(0x80040000L, "OLE_E_OLEVERB: Invalid OLEVERB structure")// OLE_E_OLEVERB
        ERR(0x80040001L, "OLE_E_ADVF: Invalid advise flags")// OLE_E_ADVF
        ERR(0x80040002L, "OLE_E_ENUM_NOMORE: Can't enumerate any more, because the associated data is missing")// OLE_E_ENUM_NOMORE
        ERR(0x80040003L, "OLE_E_ADVISENOTSUPPORTED: This implementation doesn't take advises")// OLE_E_ADVISENOTSUPPORTED
        ERR(0x80040004L, "OLE_E_NOCONNECTION: There is no connection for this connection ID")// OLE_E_NOCONNECTION
        ERR(0x80040005L, "OLE_E_NOTRUNNING: Need to run the object to perform this operation")// OLE_E_NOTRUNNING
        ERR(0x80040006L, "OLE_E_NOCACHE: There is no cache to operate on")// OLE_E_NOCACHE
        ERR(0x80040007L, "OLE_E_BLANK: Uninitialized object")// OLE_E_BLANK
        ERR(0x80040008L, "OLE_E_CLASSDIFF: Linked object's source class has changed")// OLE_E_CLASSDIFF
        ERR(0x80040009L, "OLE_E_CANT_GETMONIKER: Not able to get the moniker of the object")// OLE_E_CANT_GETMONIKER
        ERR(0x8004000AL, "OLE_E_CANT_BINDTOSOURCE: Not able to bind to the source")// OLE_E_CANT_BINDTOSOURCE
        ERR(0x8004000BL, "OLE_E_STATIC: Object is static; operation not allowed")// OLE_E_STATIC
        ERR(0x8004000CL, "OLE_E_PROMPTSAVECANCELLED: User canceled out of save dialog")// OLE_E_PROMPTSAVECANCELLED
        ERR(0x8004000DL, "OLE_E_INVALIDRECT: Invalid rectangle")// OLE_E_INVALIDRECT
        ERR(0x8004000EL, "OLE_E_WRONGCOMPOBJ: compobj.dll is too old for the ole2.dll initialized")// OLE_E_WRONGCOMPOBJ
        ERR(0x8004000FL, "OLE_E_INVALIDHWND: Invalid window handle")// OLE_E_INVALIDHWND
        ERR(0x80040010L, "OLE_E_NOT_INPLACEACTIVE: Object is not in any of the inplace active states")// OLE_E_NOT_INPLACEACTIVE
        ERR(0x80040011L, "OLE_E_CANTCONVERT: Not able to convert object")// OLE_E_CANTCONVERT
        ERR(0x80040012L, "OLE_E_NOSTORAGE: Not able to perform the operation because object is not given storage yet")// OLE_E_NOSTORAGE
        ERR(0x80040064L, "DV_E_FORMATETC: Invalid FORMATETC structure")// DV_E_FORMATETC
        ERR(0x80040065L, "DV_E_DVTARGETDEVICE: Invalid DVTARGETDEVICE structure")// DV_E_DVTARGETDEVICE
        ERR(0x80040066L, "DV_E_STGMEDIUM: Invalid STDGMEDIUM structure")// DV_E_STGMEDIUM
        ERR(0x80040067L, "DV_E_STATDATA: Invalid STATDATA structure")// DV_E_STATDATA
        ERR(0x80040068L, "DV_E_LINDEX: Invalid lindex")// DV_E_LINDEX
        ERR(0x80040069L, "DV_E_TYMED: Invalid tymed")// DV_E_TYMED
        ERR(0x8004006AL, "DV_E_CLIPFORMAT: Invalid clipboard format")// DV_E_CLIPFORMAT
        ERR(0x8004006BL, "DV_E_DVASPECT: Invalid aspect(s)")// DV_E_DVASPECT
        ERR(0x8004006CL, "DV_E_DVTARGETDEVICE_SIZE: tdSize parameter of the DVTARGETDEVICE structure is invalid")// DV_E_DVTARGETDEVICE_SIZE
        ERR(0x8004006DL, "DV_E_NOIVIEWOBJECT: Object doesn't support IViewObject interface")// DV_E_NOIVIEWOBJECT
        ERR(0x80040100L, "DRAGDROP_E_NOTREGISTERED: Trying to revoke a drop target that has not been registered")// DRAGDROP_E_NOTREGISTERED
        ERR(0x80040101L, "DRAGDROP_E_ALREADYREGISTERED: This window has already been registered as a drop target")// DRAGDROP_E_ALREADYREGISTERED
        ERR(0x80040102L, "DRAGDROP_E_INVALIDHWND: Invalid window handle")// DRAGDROP_E_INVALIDHWND
        ERR(0x80040110L, "CLASS_E_NOAGGREGATION: Class does not support aggregation (or class object is remote)")// CLASS_E_NOAGGREGATION
        ERR(0x80040111L, "CLASS_E_CLASSNOTAVAILABLE: ClassFactory cannot supply requested class")// CLASS_E_CLASSNOTAVAILABLE
        ERR(0x80040112L, "CLASS_E_NOTLICENSED: Class is not licensed for use")// CLASS_E_NOTLICENSED
        ERR(0x80040140L, "VIEW_E_DRAW: Error drawing view")// VIEW_E_DRAW
        ERR(0x80040150L, "REGDB_E_READREGDB: Could not read key from registry")// REGDB_E_READREGDB
        ERR(0x80040151L, "REGDB_E_WRITEREGDB: Could not write key to registry")// REGDB_E_WRITEREGDB
        ERR(0x80040152L, "REGDB_E_KEYMISSING: Could not find the key in the registry")// REGDB_E_KEYMISSING
        ERR(0x80040153L, "REGDB_E_INVALIDVALUE: Invalid value for registry")// REGDB_E_INVALIDVALUE
        ERR(0x80040154L, "REGDB_E_CLASSNOTREG: Class not registered")// REGDB_E_CLASSNOTREG
        ERR(0x80040155L, "REGDB_E_IIDNOTREG: Interface not registered")// REGDB_E_IIDNOTREG
        ERR(0x80040156L, "REGDB_E_BADTHREADINGMODEL: Threading model entry is not valid")// REGDB_E_BADTHREADINGMODEL
        ERR(0x80040160L, "CAT_E_CATIDNOEXIST: CATID does not exist")// CAT_E_CATIDNOEXIST
        ERR(0x80040161L, "CAT_E_NODESCRIPTION: Description not found")// CAT_E_NODESCRIPTION
        ERR(0x80040164L, "CS_E_PACKAGE_NOTFOUND: No package in the software installation data in the Active Directory meets this criteria.")// CS_E_PACKAGE_NOTFOUND
        ERR(0x80040165L, "CS_E_NOT_DELETABLE: Deleting this will break the referential integrity of the software installation data in the Active Directory.")// CS_E_NOT_DELETABLE
        ERR(0x80040166L, "CS_E_CLASS_NOTFOUND: The CLSID was not found in the software installation data in the Active Directory.")// CS_E_CLASS_NOTFOUND
        ERR(0x80040167L, "CS_E_INVALID_VERSION: The software installation data in the Active Directory is corrupt.")// CS_E_INVALID_VERSION
        ERR(0x80040168L, "CS_E_NO_CLASSSTORE: There is no software installation data in the Active Directory.")// CS_E_NO_CLASSSTORE
        ERR(0x80040169L, "CS_E_OBJECT_NOTFOUND: There is no software installation data object in the Active Directory.")// CS_E_OBJECT_NOTFOUND
        ERR(0x8004016AL, "CS_E_OBJECT_ALREADY_EXISTS: The software installation data object in the Active Directory already exists.")// CS_E_OBJECT_ALREADY_EXISTS
        ERR(0x8004016BL, "CS_E_INVALID_PATH: The path to the software installation data in the Active Directory is not correct.")// CS_E_INVALID_PATH
        ERR(0x8004016CL, "CS_E_NETWORK_ERROR: A network error interrupted the operation.")// CS_E_NETWORK_ERROR
        ERR(0x8004016DL, "CS_E_ADMIN_LIMIT_EXCEEDED: The size of this object exceeds the maximum size set by the Administrator.")// CS_E_ADMIN_LIMIT_EXCEEDED
        ERR(0x8004016EL, "CS_E_SCHEMA_MISMATCH: The schema for the software installation data in the Active Directory does not match the required schema.")// CS_E_SCHEMA_MISMATCH
        ERR(0x8004016FL, "CS_E_INTERNAL_ERROR: An error occurred in the software installation data in the Active Directory.")// CS_E_INTERNAL_ERROR
        ERR(0x80040170L, "CACHE_E_NOCACHE_UPDATED: Cache not updated")// CACHE_E_NOCACHE_UPDATED
        ERR(0x80040180L, "OLEOBJ_E_NOVERBS: No verbs for OLE object")// OLEOBJ_E_NOVERBS
        ERR(0x80040181L, "OLEOBJ_E_INVALIDVERB: Invalid verb for OLE object")// OLEOBJ_E_INVALIDVERB
        ERR(0x800401A0L, "INPLACE_E_NOTUNDOABLE: Undo is not available")// INPLACE_E_NOTUNDOABLE
        ERR(0x800401A1L, "INPLACE_E_NOTOOLSPACE: Space for tools is not available")// INPLACE_E_NOTOOLSPACE
        ERR(0x800401C0L, "CONVERT10_E_OLESTREAM_GET: OLESTREAM Get method failed")// CONVERT10_E_OLESTREAM_GET
        ERR(0x800401C1L, "CONVERT10_E_OLESTREAM_PUT: OLESTREAM Put method failed")// CONVERT10_E_OLESTREAM_PUT
        ERR(0x800401C2L, "CONVERT10_E_OLESTREAM_FMT: Contents of the OLESTREAM not in correct format")// CONVERT10_E_OLESTREAM_FMT
        ERR(0x800401C3L, "CONVERT10_E_OLESTREAM_BITMAP_TO_DIB: There was an error in a Windows GDI call while converting the bitmap to a DIB")// CONVERT10_E_OLESTREAM_BITMAP_TO_DIB
        ERR(0x800401C4L, "CONVERT10_E_STG_FMT: Contents of the IStorage not in correct format")// CONVERT10_E_STG_FMT
        ERR(0x800401C5L, "CONVERT10_E_STG_NO_STD_STREAM: Contents of IStorage is missing one of the standard streams")// CONVERT10_E_STG_NO_STD_STREAM
        ERR(0x800401C6L, "CONVERT10_E_STG_DIB_TO_BITMAP: There was an error in a Windows GDI call while converting the DIB to a bitmap.")// CONVERT10_E_STG_DIB_TO_BITMAP
        ERR(0x800401D0L, "CLIPBRD_E_CANT_OPEN: OpenClipboard Failed")// CLIPBRD_E_CANT_OPEN
        ERR(0x800401D1L, "CLIPBRD_E_CANT_EMPTY: EmptyClipboard Failed")// CLIPBRD_E_CANT_EMPTY
        ERR(0x800401D2L, "CLIPBRD_E_CANT_SET: SetClipboard Failed")// CLIPBRD_E_CANT_SET
        ERR(0x800401D3L, "CLIPBRD_E_BAD_DATA: Data on clipboard is invalid")// CLIPBRD_E_BAD_DATA
        ERR(0x800401D4L, "CLIPBRD_E_CANT_CLOSE: CloseClipboard Failed")// CLIPBRD_E_CANT_CLOSE
        ERR(0x800401E0L, "MK_E_CONNECTMANUALLY: Moniker needs to be connected manually")// MK_E_CONNECTMANUALLY
        ERR(0x800401E1L, "MK_E_EXCEEDEDDEADLINE: Operation exceeded deadline")// MK_E_EXCEEDEDDEADLINE
        ERR(0x800401E2L, "MK_E_NEEDGENERIC: Moniker needs to be generic")// MK_E_NEEDGENERIC
        ERR(0x800401E3L, "MK_E_UNAVAILABLE: Operation unavailable")// MK_E_UNAVAILABLE
        ERR(0x800401E4L, "MK_E_SYNTAX: Invalid syntax")// MK_E_SYNTAX
        ERR(0x800401E5L, "MK_E_NOOBJECT: No object for moniker")// MK_E_NOOBJECT
        ERR(0x800401E6L, "MK_E_INVALIDEXTENSION: Bad extension for file")// MK_E_INVALIDEXTENSION
        ERR(0x800401E7L, "MK_E_INTERMEDIATEINTERFACENOTSUPPORTED: Intermediate operation failed")// MK_E_INTERMEDIATEINTERFACENOTSUPPORTED
        ERR(0x800401E8L, "MK_E_NOTBINDABLE: Moniker is not bindable")// MK_E_NOTBINDABLE
        ERR(0x800401E9L, "MK_E_NOTBOUND: Moniker is not bound")// MK_E_NOTBOUND
        ERR(0x800401EAL, "MK_E_CANTOPENFILE: Moniker cannot open file")// MK_E_CANTOPENFILE
        ERR(0x800401EBL, "MK_E_MUSTBOTHERUSER: User input required for operation to succeed")// MK_E_MUSTBOTHERUSER
        ERR(0x800401ECL, "MK_E_NOINVERSE: Moniker class has no inverse")// MK_E_NOINVERSE
        ERR(0x800401EDL, "MK_E_NOSTORAGE: Moniker does not refer to storage")// MK_E_NOSTORAGE
        ERR(0x800401EEL, "MK_E_NOPREFIX: No common prefix")// MK_E_NOPREFIX
        ERR(0x800401EFL, "MK_E_ENUMERATION_FAILED: Moniker could not be enumerated")// MK_E_ENUMERATION_FAILED
        ERR(0x800401F0L, "CO_E_NOTINITIALIZED: CoInitialize has not been called.")// CO_E_NOTINITIALIZED
        ERR(0x800401F1L, "CO_E_ALREADYINITIALIZED: CoInitialize has already been called.")// CO_E_ALREADYINITIALIZED
        ERR(0x800401F2L, "CO_E_CANTDETERMINECLASS: Class of object cannot be determined")// CO_E_CANTDETERMINECLASS
        ERR(0x800401F3L, "CO_E_CLASSSTRING: Invalid class string")// CO_E_CLASSSTRING
        ERR(0x800401F4L, "CO_E_IIDSTRING: Invalid interface string")// CO_E_IIDSTRING
        ERR(0x800401F5L, "CO_E_APPNOTFOUND: Application not found")// CO_E_APPNOTFOUND
        ERR(0x800401F6L, "CO_E_APPSINGLEUSE: Application cannot be run more than once")// CO_E_APPSINGLEUSE
        ERR(0x800401F7L, "CO_E_ERRORINAPP: Some error in application program")// CO_E_ERRORINAPP
        ERR(0x800401F8L, "CO_E_DLLNOTFOUND: DLL for class not found")// CO_E_DLLNOTFOUND
        ERR(0x800401F9L, "CO_E_ERRORINDLL: Error in the DLL")// CO_E_ERRORINDLL
        ERR(0x800401FAL, "CO_E_WRONGOSFORAPP: Wrong OS or OS version for application")// CO_E_WRONGOSFORAPP
        ERR(0x800401FBL, "CO_E_OBJNOTREG: Object is not registered")// CO_E_OBJNOTREG
        ERR(0x800401FCL, "CO_E_OBJISREG: Object is already registered")// CO_E_OBJISREG
        ERR(0x800401FDL, "CO_E_OBJNOTCONNECTED: Object is not connected to server")// CO_E_OBJNOTCONNECTED
        ERR(0x800401FEL, "CO_E_APPDIDNTREG: Application was launched but it didn't register a class factory")// CO_E_APPDIDNTREG
        ERR(0x800401FFL, "CO_E_RELEASED: Object has been released")// CO_E_RELEASED
        ERR(0x00040200L, "EVENT_S_SOME_SUBSCRIBERS_FAILED: An event was able to invoke some but not all of the subscribers")// EVENT_S_SOME_SUBSCRIBERS_FAILED
        ERR(0x80040201L, "EVENT_E_ALL_SUBSCRIBERS_FAILED: An event was unable to invoke any of the subscribers")// EVENT_E_ALL_SUBSCRIBERS_FAILED
        ERR(0x00040202L, "EVENT_S_NOSUBSCRIBERS: An event was delivered but there were no subscribers")// EVENT_S_NOSUBSCRIBERS
        ERR(0x80040203L, "EVENT_E_QUERYSYNTAX: A syntax error occurred trying to evaluate a query string")// EVENT_E_QUERYSYNTAX
        ERR(0x80040204L, "EVENT_E_QUERYFIELD: An invalid field name was used in a query string")// EVENT_E_QUERYFIELD
        ERR(0x80040205L, "EVENT_E_INTERNALEXCEPTION: An unexpected exception was raised")// EVENT_E_INTERNALEXCEPTION
        ERR(0x80040206L, "EVENT_E_INTERNALERROR: An unexpected internal error was detected")// EVENT_E_INTERNALERROR
        ERR(0x80040207L, "EVENT_E_INVALID_PER_USER_SID: The owner SID on a per-user subscription doesn't exist")// EVENT_E_INVALID_PER_USER_SID
        ERR(0x80040208L, "EVENT_E_USER_EXCEPTION: A user-supplied component or subscriber raised an exception")// EVENT_E_USER_EXCEPTION
        ERR(0x80040209L, "EVENT_E_TOO_MANY_METHODS: An interface has too many methods to fire events from")// EVENT_E_TOO_MANY_METHODS
        ERR(0x8004020AL, "EVENT_E_MISSING_EVENTCLASS: A subscription cannot be stored unless its event class already exists")// EVENT_E_MISSING_EVENTCLASS
        ERR(0x8004020BL, "EVENT_E_NOT_ALL_REMOVED: Not all the objects requested could be removed")// EVENT_E_NOT_ALL_REMOVED
        ERR(0x8004020CL, "EVENT_E_COMPLUS_NOT_INSTALLED: COM+ is required for this operation, but is not installed")// EVENT_E_COMPLUS_NOT_INSTALLED
        ERR(0x8004E002L, "CONTEXT_E_ABORTED: The root transaction wanted to commit, but transaction aborted")// CONTEXT_E_ABORTED
        ERR(0x8004E003L, "CONTEXT_E_ABORTING: You made a method call on a COM+ component that has a transaction that has already aborted or in the process of aborting.")// CONTEXT_E_ABORTING
        ERR(0x8004E004L, "CONTEXT_E_NOCONTEXT: There is no MTS object context")// CONTEXT_E_NOCONTEXT
        ERR(0x8004E006L, "CONTEXT_E_SYNCH_TIMEOUT: The component is configured to use synchronization and a thread has timed out waiting to enter the context.")// CONTEXT_E_SYNCH_TIMEOUT
        ERR(0x8004E007L, "CONTEXT_E_OLDREF: You made a method call on a COM+ component that has a transaction that has already committed or aborted.")// CONTEXT_E_OLDREF
        ERR(0x8004E00CL, "CONTEXT_E_ROLENOTFOUND: The specified role was not configured for the application")// CONTEXT_E_ROLENOTFOUND
        ERR(0x8004E00FL, "CONTEXT_E_TMNOTAVAILABLE: COM+ was unable to talk to the Microsoft Distributed Transaction Coordinator")// CONTEXT_E_TMNOTAVAILABLE
        ERR(0x8004E021L, "CO_E_ACTIVATIONFAILED: An unexpected error occurred during COM+ Activation.")// CO_E_ACTIVATIONFAILED
        ERR(0x8004E022L, "CO_E_ACTIVATIONFAILED_EVENTLOGGED: COM+ Activation failed. Check the event log for more information")// CO_E_ACTIVATIONFAILED_EVENTLOGGED
        ERR(0x8004E023L, "CO_E_ACTIVATIONFAILED_CATALOGERROR: COM+ Activation failed due to a catalog or configuration error.")// CO_E_ACTIVATIONFAILED_CATALOGERROR
        ERR(0x8004E024L, "CO_E_ACTIVATIONFAILED_TIMEOUT: COM+ activation failed because the activation could not be completed in the specified amount of time.")// CO_E_ACTIVATIONFAILED_TIMEOUT
        ERR(0x8004E025L, "CO_E_INITIALIZATIONFAILED: COM+ Activation failed because an initialization function failed. Check the event log for more information.")// CO_E_INITIALIZATIONFAILED
        ERR(0x8004E026L, "CONTEXT_E_NOJIT: The requested operation requires that JIT be in the current context and it is not")// CONTEXT_E_NOJIT
        ERR(0x8004E027L, "CONTEXT_E_NOTRANSACTION: The requested operation requires that the current context have a Transaction, and it does not")// CONTEXT_E_NOTRANSACTION
        ERR(0x8004E028L, "CO_E_THREADINGMODEL_CHANGED: The components threading model has changed after install into a COM+ Application. Please re-install component.")// CO_E_THREADINGMODEL_CHANGED
        ERR(0x8004E029L, "CO_E_NOIISINTRINSICS: IIS intrinsics not available. Start your work with IIS.")// CO_E_NOIISINTRINSICS
        ERR(0x8004E02AL, "CO_E_NOCOOKIES: An attempt to write a cookie failed.")// CO_E_NOCOOKIES
        ERR(0x8004E02BL, "CO_E_DBERROR: An attempt to use a database generated a database specific error.")// CO_E_DBERROR
        ERR(0x8004E02CL, "CO_E_NOTPOOLED: The COM+ component you created must use object pooling to work.")// CO_E_NOTPOOLED
        ERR(0x8004E02DL, "CO_E_NOTCONSTRUCTED: The COM+ component you created must use object construction to work correctly.")// CO_E_NOTCONSTRUCTED
        ERR(0x8004E02EL, "CO_E_NOSYNCHRONIZATION: The COM+ component requires synchronization, and it is not configured for it.")// CO_E_NOSYNCHRONIZATION
        ERR(0x8004E02FL, "CO_E_ISOLEVELMISMATCH: The TxIsolation Level property for the COM+ component being created is stronger than the TxIsolationLevel for the \"root\" component for the transaction. The creation failed.")// CO_E_ISOLEVELMISMATCH
        ERR(0x00040000L, "OLE_S_USEREG: Use the registry database to provide the requested information")// OLE_S_USEREG
        ERR(0x00040001L, "OLE_S_STATIC: Success, but static")// OLE_S_STATIC
        ERR(0x00040002L, "OLE_S_MAC_CLIPFORMAT: Macintosh clipboard format")// OLE_S_MAC_CLIPFORMAT
        ERR(0x00040100L, "DRAGDROP_S_DROP: Successful drop took place")// DRAGDROP_S_DROP
        ERR(0x00040101L, "DRAGDROP_S_CANCEL: Drag-drop operation canceled")// DRAGDROP_S_CANCEL
        ERR(0x00040102L, "DRAGDROP_S_USEDEFAULTCURSORS: Use the default cursor")// DRAGDROP_S_USEDEFAULTCURSORS
        ERR(0x00040130L, "DATA_S_SAMEFORMATETC: Data has same FORMATETC")// DATA_S_SAMEFORMATETC
        ERR(0x00040140L, "VIEW_S_ALREADY_FROZEN: View is already frozen")// VIEW_S_ALREADY_FROZEN
        ERR(0x00040170L, "CACHE_S_FORMATETC_NOTSUPPORTED: FORMATETC not supported")// CACHE_S_FORMATETC_NOTSUPPORTED
        ERR(0x00040171L, "CACHE_S_SAMECACHE: Same cache")// CACHE_S_SAMECACHE
        ERR(0x00040172L, "CACHE_S_SOMECACHES_NOTUPDATED: Some cache(s) not updated")// CACHE_S_SOMECACHES_NOTUPDATED
        ERR(0x00040180L, "OLEOBJ_S_INVALIDVERB: Invalid verb for OLE object")// OLEOBJ_S_INVALIDVERB
        ERR(0x00040181L, "OLEOBJ_S_CANNOT_DOVERB_NOW: Verb number is valid but verb cannot be done now")// OLEOBJ_S_CANNOT_DOVERB_NOW
        ERR(0x00040182L, "OLEOBJ_S_INVALIDHWND: Invalid window handle passed")// OLEOBJ_S_INVALIDHWND
        ERR(0x000401A0L, "INPLACE_S_TRUNCATED: Message is too long; some of it had to be truncated before displaying")// INPLACE_S_TRUNCATED
        ERR(0x000401C0L, "CONVERT10_S_NO_PRESENTATION: Unable to convert OLESTREAM to IStorage")// CONVERT10_S_NO_PRESENTATION
        ERR(0x000401E2L, "MK_S_REDUCED_TO_SELF: Moniker reduced to itself")// MK_S_REDUCED_TO_SELF
        ERR(0x000401E4L, "MK_S_ME: Common prefix is this moniker")// MK_S_ME
        ERR(0x000401E5L, "MK_S_HIM: Common prefix is input moniker")// MK_S_HIM
        ERR(0x000401E6L, "MK_S_US: Common prefix is both monikers")// MK_S_US
        ERR(0x000401E7L, "MK_S_MONIKERALREADYREGISTERED: Moniker is already registered in running object table")// MK_S_MONIKERALREADYREGISTERED
        ERR(0x00041300L, "SCHED_S_TASK_READY: The task is ready to run at its next scheduled time.")// SCHED_S_TASK_READY
        ERR(0x00041301L, "SCHED_S_TASK_RUNNING: The task is currently running.")// SCHED_S_TASK_RUNNING
        ERR(0x00041302L, "SCHED_S_TASK_DISABLED: The task will not run at the scheduled times because it has been disabled.")// SCHED_S_TASK_DISABLED
        ERR(0x00041303L, "SCHED_S_TASK_HAS_NOT_RUN: The task has not yet run.")// SCHED_S_TASK_HAS_NOT_RUN
        ERR(0x00041304L, "SCHED_S_TASK_NO_MORE_RUNS: There are no more runs scheduled for this task.")// SCHED_S_TASK_NO_MORE_RUNS
        ERR(0x00041305L, "SCHED_S_TASK_NOT_SCHEDULED: One or more of the properties that are needed to run this task on a schedule have not been set.")// SCHED_S_TASK_NOT_SCHEDULED
        ERR(0x00041306L, "SCHED_S_TASK_TERMINATED: The last run of the task was terminated by the user.")// SCHED_S_TASK_TERMINATED
        ERR(0x00041307L, "SCHED_S_TASK_NO_VALID_TRIGGERS: Either the task has no triggers or the existing triggers are disabled or not set.")// SCHED_S_TASK_NO_VALID_TRIGGERS
        ERR(0x00041308L, "SCHED_S_EVENT_TRIGGER: Event triggers don't have set run times.")// SCHED_S_EVENT_TRIGGER
        ERR(0x80041309L, "SCHED_E_TRIGGER_NOT_FOUND: Trigger not found.")// SCHED_E_TRIGGER_NOT_FOUND
        ERR(0x8004130AL, "SCHED_E_TASK_NOT_READY: One or more of the properties that are needed to run this task have not been set.")// SCHED_E_TASK_NOT_READY
        ERR(0x8004130BL, "SCHED_E_TASK_NOT_RUNNING: There is no running instance of the task to terminate.")// SCHED_E_TASK_NOT_RUNNING
        ERR(0x8004130CL, "SCHED_E_SERVICE_NOT_INSTALLED: The Task Scheduler Service is not installed on this computer.")// SCHED_E_SERVICE_NOT_INSTALLED
        ERR(0x8004130DL, "SCHED_E_CANNOT_OPEN_TASK: The task object could not be opened.")// SCHED_E_CANNOT_OPEN_TASK
        ERR(0x8004130EL, "SCHED_E_INVALID_TASK: The object is either an invalid task object or is not a task object.")// SCHED_E_INVALID_TASK
        ERR(0x8004130FL, "SCHED_E_ACCOUNT_INFORMATION_NOT_SET: No account information could be found in the Task Scheduler security database for the task indicated.")// SCHED_E_ACCOUNT_INFORMATION_NOT_SET
        ERR(0x80041310L, "SCHED_E_ACCOUNT_NAME_NOT_FOUND: Unable to establish existence of the account specified.")// SCHED_E_ACCOUNT_NAME_NOT_FOUND
        ERR(0x80041311L, "SCHED_E_ACCOUNT_DBASE_CORRUPT: Corruption was detected in the Task Scheduler security database; the database has been reset.")// SCHED_E_ACCOUNT_DBASE_CORRUPT
        ERR(0x80041312L, "SCHED_E_NO_SECURITY_SERVICES: Task Scheduler security services are available only on Windows NT.")// SCHED_E_NO_SECURITY_SERVICES
        ERR(0x80041313L, "SCHED_E_UNKNOWN_OBJECT_VERSION: The task object version is either unsupported or invalid.")// SCHED_E_UNKNOWN_OBJECT_VERSION
        ERR(0x80041314L, "SCHED_E_UNSUPPORTED_ACCOUNT_OPTION: The task has been configured with an unsupported combination of account settings and run time options.")// SCHED_E_UNSUPPORTED_ACCOUNT_OPTION
        ERR(0x80041315L, "SCHED_E_SERVICE_NOT_RUNNING: The Task Scheduler Service is not running.")// SCHED_E_SERVICE_NOT_RUNNING
        ERR(0x80080001L, "CO_E_CLASS_CREATE_FAILED: Attempt to create a class object failed")// CO_E_CLASS_CREATE_FAILED
        ERR(0x80080002L, "CO_E_SCM_ERROR: OLE service could not bind object")// CO_E_SCM_ERROR
        ERR(0x80080003L, "CO_E_SCM_RPC_FAILURE: RPC communication failed with OLE service")// CO_E_SCM_RPC_FAILURE
        ERR(0x80080004L, "CO_E_BAD_PATH: Bad path to object")// CO_E_BAD_PATH
        ERR(0x80080005L, "CO_E_SERVER_EXEC_FAILURE: Server execution failed")// CO_E_SERVER_EXEC_FAILURE
        ERR(0x80080006L, "CO_E_OBJSRV_RPC_FAILURE: OLE service could not communicate with the object server")// CO_E_OBJSRV_RPC_FAILURE
        ERR(0x80080007L, "MK_E_NO_NORMALIZED: Moniker path could not be normalized")// MK_E_NO_NORMALIZED
        ERR(0x80080008L, "CO_E_SERVER_STOPPING: Object server is stopping when OLE service contacts it")// CO_E_SERVER_STOPPING
        ERR(0x80080009L, "MEM_E_INVALID_ROOT: An invalid root block pointer was specified")// MEM_E_INVALID_ROOT
        ERR(0x80080010L, "MEM_E_INVALID_LINK: An allocation chain contained an invalid link pointer")// MEM_E_INVALID_LINK
        ERR(0x80080011L, "MEM_E_INVALID_SIZE: The requested allocation size was too large")// MEM_E_INVALID_SIZE
        ERR(0x00080012L, "CO_S_NOTALLINTERFACES: Not all the requested interfaces were available")// CO_S_NOTALLINTERFACES
        ERR(0x00080013L, "CO_S_MACHINENAMENOTFOUND: The specified machine name was not found in the cache.")// CO_S_MACHINENAMENOTFOUND
        ERR(0x80020001L, "DISP_E_UNKNOWNINTERFACE: Unknown interface.")// DISP_E_UNKNOWNINTERFACE
        ERR(0x80020003L, "DISP_E_MEMBERNOTFOUND: Member not found.")// DISP_E_MEMBERNOTFOUND
        ERR(0x80020004L, "DISP_E_PARAMNOTFOUND: Parameter not found.")// DISP_E_PARAMNOTFOUND
        ERR(0x80020005L, "DISP_E_TYPEMISMATCH: Type mismatch.")// DISP_E_TYPEMISMATCH
        ERR(0x80020006L, "DISP_E_UNKNOWNNAME: Unknown name.")// DISP_E_UNKNOWNNAME
        ERR(0x80020007L, "DISP_E_NONAMEDARGS: No named arguments.")// DISP_E_NONAMEDARGS
        ERR(0x80020008L, "DISP_E_BADVARTYPE: Bad variable type.")// DISP_E_BADVARTYPE
        ERR(0x80020009L, "DISP_E_EXCEPTION: Exception occurred.")// DISP_E_EXCEPTION
        ERR(0x8002000AL, "DISP_E_OVERFLOW: Out of present range.")// DISP_E_OVERFLOW
        ERR(0x8002000BL, "DISP_E_BADINDEX: Invalid index.")// DISP_E_BADINDEX
        ERR(0x8002000CL, "DISP_E_UNKNOWNLCID: Unknown language.")// DISP_E_UNKNOWNLCID
        ERR(0x8002000DL, "DISP_E_ARRAYISLOCKED: Memory is locked.")// DISP_E_ARRAYISLOCKED
        ERR(0x8002000EL, "DISP_E_BADPARAMCOUNT: Invalid number of parameters.")// DISP_E_BADPARAMCOUNT
        ERR(0x8002000FL, "DISP_E_PARAMNOTOPTIONAL: Parameter not optional.")// DISP_E_PARAMNOTOPTIONAL
        ERR(0x80020010L, "DISP_E_BADCALLEE: Invalid callee.")// DISP_E_BADCALLEE
        ERR(0x80020011L, "DISP_E_NOTACOLLECTION: Does not support a collection.")// DISP_E_NOTACOLLECTION
        ERR(0x80020012L, "DISP_E_DIVBYZERO: Division by zero.")// DISP_E_DIVBYZERO
        ERR(0x80020013L, "DISP_E_BUFFERTOOSMALL: Buffer too small")// DISP_E_BUFFERTOOSMALL
        ERR(0x80028016L, "TYPE_E_BUFFERTOOSMALL: Buffer too small.")// TYPE_E_BUFFERTOOSMALL
        ERR(0x80028017L, "TYPE_E_FIELDNOTFOUND: Field name not defined in the record.")// TYPE_E_FIELDNOTFOUND
        ERR(0x80028018L, "TYPE_E_INVDATAREAD: Old format or invalid type library.")// TYPE_E_INVDATAREAD
        ERR(0x80028019L, "TYPE_E_UNSUPFORMAT: Old format or invalid type library.")// TYPE_E_UNSUPFORMAT
        ERR(0x8002801CL, "TYPE_E_REGISTRYACCESS: Error accessing the OLE registry.")// TYPE_E_REGISTRYACCESS
        ERR(0x8002801DL, "TYPE_E_LIBNOTREGISTERED: Library not registered.")// TYPE_E_LIBNOTREGISTERED
        ERR(0x80028027L, "TYPE_E_UNDEFINEDTYPE: Bound to unknown type.")// TYPE_E_UNDEFINEDTYPE
        ERR(0x80028028L, "TYPE_E_QUALIFIEDNAMEDISALLOWED: Qualified name disallowed.")// TYPE_E_QUALIFIEDNAMEDISALLOWED
        ERR(0x80028029L, "TYPE_E_INVALIDSTATE: Invalid forward reference, or reference to uncompiled type.")// TYPE_E_INVALIDSTATE
        ERR(0x8002802AL, "TYPE_E_WRONGTYPEKIND: Type mismatch.")// TYPE_E_WRONGTYPEKIND
        ERR(0x8002802BL, "TYPE_E_ELEMENTNOTFOUND: Element not found.")// TYPE_E_ELEMENTNOTFOUND
        ERR(0x8002802CL, "TYPE_E_AMBIGUOUSNAME: Ambiguous name.")// TYPE_E_AMBIGUOUSNAME
        ERR(0x8002802DL, "TYPE_E_NAMECONFLICT: Name already exists in the library.")// TYPE_E_NAMECONFLICT
        ERR(0x8002802EL, "TYPE_E_UNKNOWNLCID: Unknown LCID.")// TYPE_E_UNKNOWNLCID
        ERR(0x8002802FL, "TYPE_E_DLLFUNCTIONNOTFOUND: Function not defined in specified DLL.")// TYPE_E_DLLFUNCTIONNOTFOUND
        ERR(0x800288BDL, "TYPE_E_BADMODULEKIND: Wrong module kind for the operation.")// TYPE_E_BADMODULEKIND
        ERR(0x800288C5L, "TYPE_E_SIZETOOBIG: Size may not exceed 64K.")// TYPE_E_SIZETOOBIG
        ERR(0x800288C6L, "TYPE_E_DUPLICATEID: Duplicate ID in inheritance hierarchy.")// TYPE_E_DUPLICATEID
        ERR(0x800288CFL, "TYPE_E_INVALIDID: Incorrect inheritance depth in standard OLE hmember.")// TYPE_E_INVALIDID
        ERR(0x80028CA0L, "TYPE_E_TYPEMISMATCH: Type mismatch.")// TYPE_E_TYPEMISMATCH
        ERR(0x80028CA1L, "TYPE_E_OUTOFBOUNDS: Invalid number of arguments.")// TYPE_E_OUTOFBOUNDS
        ERR(0x80028CA2L, "TYPE_E_IOERROR: I/O Error.")// TYPE_E_IOERROR
        ERR(0x80028CA3L, "TYPE_E_CANTCREATETMPFILE: Error creating unique tmp file.")// TYPE_E_CANTCREATETMPFILE
        ERR(0x80029C4AL, "TYPE_E_CANTLOADLIBRARY: Error loading type library/DLL.")// TYPE_E_CANTLOADLIBRARY
        ERR(0x80029C83L, "TYPE_E_INCONSISTENTPROPFUNCS: Inconsistent property functions.")// TYPE_E_INCONSISTENTPROPFUNCS
        ERR(0x80029C84L, "TYPE_E_CIRCULARTYPE: Circular dependency between types/modules.")// TYPE_E_CIRCULARTYPE
        ERR(0x80030001L, "STG_E_INVALIDFUNCTION: Unable to perform requested operation.")// STG_E_INVALIDFUNCTION
        ERR(0x80030002L, "STG_E_FILENOTFOUND: %1 could not be found.")// STG_E_FILENOTFOUND
        ERR(0x80030003L, "STG_E_PATHNOTFOUND: The path %1 could not be found.")// STG_E_PATHNOTFOUND
        ERR(0x80030004L, "STG_E_TOOMANYOPENFILES: There are insufficient resources to open another file.")// STG_E_TOOMANYOPENFILES
        ERR(0x80030005L, "STG_E_ACCESSDENIED: Access Denied.")// STG_E_ACCESSDENIED
        ERR(0x80030006L, "STG_E_INVALIDHANDLE: Attempted an operation on an invalid object.")// STG_E_INVALIDHANDLE
        ERR(0x80030008L, "STG_E_INSUFFICIENTMEMORY: There is insufficient memory available to complete operation.")// STG_E_INSUFFICIENTMEMORY
        ERR(0x80030009L, "STG_E_INVALIDPOINTER: Invalid pointer error.")// STG_E_INVALIDPOINTER
        ERR(0x80030012L, "STG_E_NOMOREFILES: There are no more entries to return.")// STG_E_NOMOREFILES
        ERR(0x80030013L, "STG_E_DISKISWRITEPROTECTED: Disk is write-protected.")// STG_E_DISKISWRITEPROTECTED
        ERR(0x80030019L, "STG_E_SEEKERROR: An error occurred during a seek operation.")// STG_E_SEEKERROR
        ERR(0x8003001DL, "STG_E_WRITEFAULT: A disk error occurred during a write operation.")// STG_E_WRITEFAULT
        ERR(0x8003001EL, "STG_E_READFAULT: A disk error occurred during a read operation.")// STG_E_READFAULT
        ERR(0x80030020L, "STG_E_SHAREVIOLATION: A share violation has occurred.")// STG_E_SHAREVIOLATION
        ERR(0x80030021L, "STG_E_LOCKVIOLATION: A lock violation has occurred.")// STG_E_LOCKVIOLATION
        ERR(0x80030050L, "STG_E_FILEALREADYEXISTS: %1 already exists.")// STG_E_FILEALREADYEXISTS
        ERR(0x80030057L, "STG_E_INVALIDPARAMETER: Invalid parameter error.")// STG_E_INVALIDPARAMETER
        ERR(0x80030070L, "STG_E_MEDIUMFULL: There is insufficient disk space to complete operation.")// STG_E_MEDIUMFULL
        ERR(0x800300F0L, "STG_E_PROPSETMISMATCHED: Illegal write of non-simple property to simple property set.")// STG_E_PROPSETMISMATCHED
        ERR(0x800300FAL, "STG_E_ABNORMALAPIEXIT: An API call exited abnormally.")// STG_E_ABNORMALAPIEXIT
        ERR(0x800300FBL, "STG_E_INVALIDHEADER: The file %1 is not a valid compound file.")// STG_E_INVALIDHEADER
        ERR(0x800300FCL, "STG_E_INVALIDNAME: The name %1 is not valid.")// STG_E_INVALIDNAME
        ERR(0x800300FDL, "STG_E_UNKNOWN: An unexpected error occurred.")// STG_E_UNKNOWN
        ERR(0x800300FEL, "STG_E_UNIMPLEMENTEDFUNCTION: That function is not implemented.")// STG_E_UNIMPLEMENTEDFUNCTION
        ERR(0x800300FFL, "STG_E_INVALIDFLAG: Invalid flag error.")// STG_E_INVALIDFLAG
        ERR(0x80030100L, "STG_E_INUSE: Attempted to use an object that is busy.")// STG_E_INUSE
        ERR(0x80030101L, "STG_E_NOTCURRENT: The storage has been changed since the last commit.")// STG_E_NOTCURRENT
        ERR(0x80030102L, "STG_E_REVERTED: Attempted to use an object that has ceased to exist.")// STG_E_REVERTED
        ERR(0x80030103L, "STG_E_CANTSAVE: Can't save.")// STG_E_CANTSAVE
        ERR(0x80030104L, "STG_E_OLDFORMAT: The compound file %1 was produced with an incompatible version of storage.")// STG_E_OLDFORMAT
        ERR(0x80030105L, "STG_E_OLDDLL: The compound file %1 was produced with a newer version of storage.")// STG_E_OLDDLL
        ERR(0x80030106L, "STG_E_SHAREREQUIRED: Share.exe or equivalent is required for operation.")// STG_E_SHAREREQUIRED
        ERR(0x80030107L, "STG_E_NOTFILEBASEDSTORAGE: Illegal operation called on non-file based storage.")// STG_E_NOTFILEBASEDSTORAGE
        ERR(0x80030108L, "STG_E_EXTANTMARSHALLINGS: Illegal operation called on object with extant marshallings.")// STG_E_EXTANTMARSHALLINGS
        ERR(0x80030109L, "STG_E_DOCFILECORRUPT: The docfile has been corrupted.")// STG_E_DOCFILECORRUPT
        ERR(0x80030110L, "STG_E_BADBASEADDRESS: OLE32.DLL has been loaded at the wrong address.")// STG_E_BADBASEADDRESS
        ERR(0x80030111L, "STG_E_DOCFILETOOLARGE: The compound file is too large for the current implementation")// STG_E_DOCFILETOOLARGE
        ERR(0x80030112L, "STG_E_NOTSIMPLEFORMAT: The compound file was not created with the STGM_SIMPLE flag")// STG_E_NOTSIMPLEFORMAT
        ERR(0x80030201L, "STG_E_INCOMPLETE: The file download was aborted abnormally. The file is incomplete.")// STG_E_INCOMPLETE
        ERR(0x80030202L, "STG_E_TERMINATED: The file download has been terminated.")// STG_E_TERMINATED
        ERR(0x00030200L, "STG_S_CONVERTED: The underlying file was converted to compound file format.")// STG_S_CONVERTED
        ERR(0x00030201L, "STG_S_BLOCK: The storage operation should block until more data is available.")// STG_S_BLOCK
        ERR(0x00030202L, "STG_S_RETRYNOW: The storage operation should retry immediately.")// STG_S_RETRYNOW
        ERR(0x00030203L, "STG_S_MONITORING: The notified event sink will not influence the storage operation.")// STG_S_MONITORING
        ERR(0x00030204L, "STG_S_MULTIPLEOPENS: Multiple opens prevent consolidated. (commit succeeded).")// STG_S_MULTIPLEOPENS
        ERR(0x00030205L, "STG_S_CONSOLIDATIONFAILED: Consolidation of the storage file failed. (commit succeeded).")// STG_S_CONSOLIDATIONFAILED
        ERR(0x00030206L, "STG_S_CANNOTCONSOLIDATE: Consolidation of the storage file is inappropriate. (commit succeeded).")// STG_S_CANNOTCONSOLIDATE
        ERR(0x80010001L, "RPC_E_CALL_REJECTED: Call was rejected by callee.")// RPC_E_CALL_REJECTED
        ERR(0x80010002L, "RPC_E_CALL_CANCELED: Call was canceled by the message filter.")// RPC_E_CALL_CANCELED
        ERR(0x80010003L, "RPC_E_CANTPOST_INSENDCALL: The caller is dispatching an intertask SendMessage call and cannot call out via PostMessage.")// RPC_E_CANTPOST_INSENDCALL
        ERR(0x80010004L, "RPC_E_CANTCALLOUT_INASYNCCALL: The caller is dispatching an asynchronous call and cannot make an outgoing call on behalf of this call.")// RPC_E_CANTCALLOUT_INASYNCCALL
        ERR(0x80010005L, "RPC_E_CANTCALLOUT_INEXTERNALCALL: It is illegal to call out while inside message filter.")// RPC_E_CANTCALLOUT_INEXTERNALCALL
        ERR(0x80010006L, "RPC_E_CONNECTION_TERMINATED: The connection terminated or is in a bogus state and cannot be used any more. Other connections are still valid.")// RPC_E_CONNECTION_TERMINATED
        ERR(0x80010007L, "RPC_E_SERVER_DIED: The callee (server [not server application]) is not available and disappeared; all connections are invalid. The call may have executed.")// RPC_E_SERVER_DIED
        ERR(0x80010008L, "RPC_E_CLIENT_DIED: The caller (client) disappeared while the callee (server) was processing a call.")// RPC_E_CLIENT_DIED
        ERR(0x80010009L, "RPC_E_INVALID_DATAPACKET: The data packet with the marshalled parameter data is incorrect.")// RPC_E_INVALID_DATAPACKET
        ERR(0x8001000AL, "RPC_E_CANTTRANSMIT_CALL: The call was not transmitted properly; the message queue was full and was not emptied after yielding.")// RPC_E_CANTTRANSMIT_CALL
        ERR(0x8001000BL, "RPC_E_CLIENT_CANTMARSHAL_DATA: The client (caller) cannot marshall the parameter data - low memory, etc.")// RPC_E_CLIENT_CANTMARSHAL_DATA
        ERR(0x8001000CL, "RPC_E_CLIENT_CANTUNMARSHAL_DATA: The client (caller) cannot unmarshall the return data - low memory, etc.")// RPC_E_CLIENT_CANTUNMARSHAL_DATA
        ERR(0x8001000DL, "RPC_E_SERVER_CANTMARSHAL_DATA: The server (callee) cannot marshall the return data - low memory, etc.")// RPC_E_SERVER_CANTMARSHAL_DATA
        ERR(0x8001000EL, "RPC_E_SERVER_CANTUNMARSHAL_DATA: The server (callee) cannot unmarshall the parameter data - low memory, etc.")// RPC_E_SERVER_CANTUNMARSHAL_DATA
        ERR(0x8001000FL, "RPC_E_INVALID_DATA: Received data is invalid; could be server or client data.")// RPC_E_INVALID_DATA
        ERR(0x80010010L, "RPC_E_INVALID_PARAMETER: A particular parameter is invalid and cannot be (un)marshalled.")// RPC_E_INVALID_PARAMETER
        ERR(0x80010011L, "RPC_E_CANTCALLOUT_AGAIN: There is no second outgoing call on same channel in DDE conversation.")// RPC_E_CANTCALLOUT_AGAIN
        ERR(0x80010012L, "RPC_E_SERVER_DIED_DNE: The callee (server [not server application]) is not available and disappeared; all connections are invalid. The call did not execute.")// RPC_E_SERVER_DIED_DNE
        ERR(0x80010100L, "RPC_E_SYS_CALL_FAILED: System call failed.")// RPC_E_SYS_CALL_FAILED
        ERR(0x80010101L, "RPC_E_OUT_OF_RESOURCES: Could not allocate some required resource (memory, events, ...)")// RPC_E_OUT_OF_RESOURCES
        ERR(0x80010102L, "RPC_E_ATTEMPTED_MULTITHREAD: Attempted to make calls on more than one thread in single threaded mode.")// RPC_E_ATTEMPTED_MULTITHREAD
        ERR(0x80010103L, "RPC_E_NOT_REGISTERED: The requested interface is not registered on the server object.")// RPC_E_NOT_REGISTERED
        ERR(0x80010104L, "RPC_E_FAULT: RPC could not call the server or could not return the results of calling the server.")// RPC_E_FAULT
        ERR(0x80010105L, "RPC_E_SERVERFAULT: The server threw an exception.")// RPC_E_SERVERFAULT
        ERR(0x80010106L, "RPC_E_CHANGED_MODE: Cannot change thread mode after it is set.")// RPC_E_CHANGED_MODE
        ERR(0x80010107L, "RPC_E_INVALIDMETHOD: The method called does not exist on the server.")// RPC_E_INVALIDMETHOD
        ERR(0x80010108L, "RPC_E_DISCONNECTED: The object invoked has disconnected from its clients.")// RPC_E_DISCONNECTED
        ERR(0x80010109L, "RPC_E_RETRY: The object invoked chose not to process the call now. Try again later.")// RPC_E_RETRY
        ERR(0x8001010AL, "RPC_E_SERVERCALL_RETRYLATER: The message filter indicated that the application is busy.")// RPC_E_SERVERCALL_RETRYLATER
        ERR(0x8001010BL, "RPC_E_SERVERCALL_REJECTED: The message filter rejected the call.")// RPC_E_SERVERCALL_REJECTED
        ERR(0x8001010CL, "RPC_E_INVALID_CALLDATA: A call control interfaces was called with invalid data.")// RPC_E_INVALID_CALLDATA
        ERR(0x8001010DL, "RPC_E_CANTCALLOUT_ININPUTSYNCCALL: An outgoing call cannot be made since the application is dispatching an input-synchronous call.")// RPC_E_CANTCALLOUT_ININPUTSYNCCALL
        ERR(0x8001010EL, "RPC_E_WRONG_THREAD: The application called an interface that was marshalled for a different thread.")// RPC_E_WRONG_THREAD
        ERR(0x8001010FL, "RPC_E_THREAD_NOT_INIT: CoInitialize has not been called on the current thread.")// RPC_E_THREAD_NOT_INIT
        ERR(0x80010110L, "RPC_E_VERSION_MISMATCH: The version of OLE on the client and server machines does not match.")// RPC_E_VERSION_MISMATCH
        ERR(0x80010111L, "RPC_E_INVALID_HEADER: OLE received a packet with an invalid header.")// RPC_E_INVALID_HEADER
        ERR(0x80010112L, "RPC_E_INVALID_EXTENSION: OLE received a packet with an invalid extension.")// RPC_E_INVALID_EXTENSION
        ERR(0x80010113L, "RPC_E_INVALID_IPID: The requested object or interface does not exist.")// RPC_E_INVALID_IPID
        ERR(0x80010114L, "RPC_E_INVALID_OBJECT: The requested object does not exist.")// RPC_E_INVALID_OBJECT
        ERR(0x80010115L, "RPC_S_CALLPENDING: OLE has sent a request and is waiting for a reply.")// RPC_S_CALLPENDING
        ERR(0x80010116L, "RPC_S_WAITONTIMER: OLE is waiting before retrying a request.")// RPC_S_WAITONTIMER
        ERR(0x80010117L, "RPC_E_CALL_COMPLETE: Call context cannot be accessed after call completed.")// RPC_E_CALL_COMPLETE
        ERR(0x80010118L, "RPC_E_UNSECURE_CALL: Impersonate on unsecure calls is not supported.")// RPC_E_UNSECURE_CALL
        ERR(0x80010119L, "RPC_E_TOO_LATE: Security must be initialized before any interfaces are marshalled or unmarshalled. It cannot be changed once initialized.")// RPC_E_TOO_LATE
        ERR(0x8001011AL, "RPC_E_NO_GOOD_SECURITY_PACKAGES: No security packages are installed on this machine or the user is not logged on or there are no compatible security packages between the client and server.")// RPC_E_NO_GOOD_SECURITY_PACKAGES
        ERR(0x8001011BL, "RPC_E_ACCESS_DENIED: Access is denied.")// RPC_E_ACCESS_DENIED
        ERR(0x8001011CL, "RPC_E_REMOTE_DISABLED: Remote calls are not allowed for this process.")// RPC_E_REMOTE_DISABLED
        ERR(0x8001011DL, "RPC_E_INVALID_OBJREF: The marshaled interface data packet (OBJREF) has an invalid or unknown format.")// RPC_E_INVALID_OBJREF
        ERR(0x8001011EL, "RPC_E_NO_CONTEXT: No context is associated with this call. This happens for some custom marshalled calls and on the client side of the call.")// RPC_E_NO_CONTEXT
        ERR(0x8001011FL, "RPC_E_TIMEOUT: This operation returned because the timeout period expired.")// RPC_E_TIMEOUT
        ERR(0x80010120L, "RPC_E_NO_SYNC: There are no synchronize objects to wait on.")// RPC_E_NO_SYNC
        ERR(0x80010121L, "RPC_E_FULLSIC_REQUIRED: Full subject issuer chain SSL principal name expected from the server.")// RPC_E_FULLSIC_REQUIRED
        ERR(0x80010122L, "RPC_E_INVALID_STD_NAME: Principal name is not a valid MSSTD name.")// RPC_E_INVALID_STD_NAME
        ERR(0x80010123L, "CO_E_FAILEDTOIMPERSONATE: Unable to impersonate DCOM client")// CO_E_FAILEDTOIMPERSONATE
        ERR(0x80010124L, "CO_E_FAILEDTOGETSECCTX: Unable to obtain server's security context")// CO_E_FAILEDTOGETSECCTX
        ERR(0x80010125L, "CO_E_FAILEDTOOPENTHREADTOKEN: Unable to open the access token of the current thread")// CO_E_FAILEDTOOPENTHREADTOKEN
        ERR(0x80010126L, "CO_E_FAILEDTOGETTOKENINFO: Unable to obtain user info from an access token")// CO_E_FAILEDTOGETTOKENINFO
        ERR(0x80010127L, "CO_E_TRUSTEEDOESNTMATCHCLIENT: The client who called IAccessControl::IsAccessPermitted was not the trustee provided to the method")// CO_E_TRUSTEEDOESNTMATCHCLIENT
        ERR(0x80010128L, "CO_E_FAILEDTOQUERYCLIENTBLANKET: Unable to obtain the client's security blanket")// CO_E_FAILEDTOQUERYCLIENTBLANKET
        ERR(0x80010129L, "CO_E_FAILEDTOSETDACL: Unable to set a discretionary ACL into a security descriptor")// CO_E_FAILEDTOSETDACL
        ERR(0x8001012AL, "CO_E_ACCESSCHECKFAILED: The system function, AccessCheck, returned false")// CO_E_ACCESSCHECKFAILED
        ERR(0x8001012BL, "CO_E_NETACCESSAPIFAILED: Either NetAccessDel or NetAccessAdd returned an error code.")// CO_E_NETACCESSAPIFAILED
        ERR(0x8001012CL, "CO_E_WRONGTRUSTEENAMESYNTAX: One of the trustee strings provided by the user did not conform to the <Domain>\\<Name> syntax and it was not the \"*\" string")// CO_E_WRONGTRUSTEENAMESYNTAX
        ERR(0x8001012DL, "CO_E_INVALIDSID: One of the security identifiers provided by the user was invalid")// CO_E_INVALIDSID
        ERR(0x8001012EL, "CO_E_CONVERSIONFAILED: Unable to convert a wide character trustee string to a multibyte trustee string")// CO_E_CONVERSIONFAILED
        ERR(0x8001012FL, "CO_E_NOMATCHINGSIDFOUND: Unable to find a security identifier that corresponds to a trustee string provided by the user")// CO_E_NOMATCHINGSIDFOUND
        ERR(0x80010130L, "CO_E_LOOKUPACCSIDFAILED: The system function, LookupAccountSID, failed")// CO_E_LOOKUPACCSIDFAILED
        ERR(0x80010131L, "CO_E_NOMATCHINGNAMEFOUND: Unable to find a trustee name that corresponds to a security identifier provided by the user")// CO_E_NOMATCHINGNAMEFOUND
        ERR(0x80010132L, "CO_E_LOOKUPACCNAMEFAILED: The system function, LookupAccountName, failed")// CO_E_LOOKUPACCNAMEFAILED
        ERR(0x80010133L, "CO_E_SETSERLHNDLFAILED: Unable to set or reset a serialization handle")// CO_E_SETSERLHNDLFAILED
        ERR(0x80010134L, "CO_E_FAILEDTOGETWINDIR: Unable to obtain the Windows directory")// CO_E_FAILEDTOGETWINDIR
        ERR(0x80010135L, "CO_E_PATHTOOLONG: Path too long")// CO_E_PATHTOOLONG
        ERR(0x80010136L, "CO_E_FAILEDTOGENUUID: Unable to generate a uuid.")// CO_E_FAILEDTOGENUUID
        ERR(0x80010137L, "CO_E_FAILEDTOCREATEFILE: Unable to create file")// CO_E_FAILEDTOCREATEFILE
        ERR(0x80010138L, "CO_E_FAILEDTOCLOSEHANDLE: Unable to close a serialization handle or a file handle.")// CO_E_FAILEDTOCLOSEHANDLE
        ERR(0x80010139L, "CO_E_EXCEEDSYSACLLIMIT: The number of ACEs in an ACL exceeds the system limit.")// CO_E_EXCEEDSYSACLLIMIT
        ERR(0x8001013AL, "CO_E_ACESINWRONGORDER: Not all the DENY_ACCESS ACEs are arranged in front of the GRANT_ACCESS ACEs in the stream.")// CO_E_ACESINWRONGORDER
        ERR(0x8001013BL, "CO_E_INCOMPATIBLESTREAMVERSION: The version of ACL format in the stream is not supported by this implementation of IAccessControl")// CO_E_INCOMPATIBLESTREAMVERSION
        ERR(0x8001013CL, "CO_E_FAILEDTOOPENPROCESSTOKEN: Unable to open the access token of the server process")// CO_E_FAILEDTOOPENPROCESSTOKEN
        ERR(0x8001013DL, "CO_E_DECODEFAILED: Unable to decode the ACL in the stream provided by the user")// CO_E_DECODEFAILED
        ERR(0x8001013FL, "CO_E_ACNOTINITIALIZED: The COM IAccessControl object is not initialized")// CO_E_ACNOTINITIALIZED
        ERR(0x80010140L, "CO_E_CANCEL_DISABLED: Call Cancellation is disabled")// CO_E_CANCEL_DISABLED
        ERR(0x8001FFFFL, "RPC_E_UNEXPECTED: An internal error occurred.")// RPC_E_UNEXPECTED
        ERR(0xC0090001L, "ERROR_AUDITING_DISABLED: The specified event is currently not being audited.")// ERROR_AUDITING_DISABLED
        ERR(0x80090001L, "NTE_BAD_UID: Bad UID.")// NTE_BAD_UID
        ERR(0x80090002L, "NTE_BAD_HASH: Bad Hash.")// NTE_BAD_HASH
        ERR(0x80090003L, "NTE_BAD_KEY: Bad Key.")// NTE_BAD_KEY
        ERR(0x80090004L, "NTE_BAD_LEN: Bad Length.")// NTE_BAD_LEN
        ERR(0x80090005L, "NTE_BAD_DATA: Bad Data.")// NTE_BAD_DATA
        ERR(0x80090006L, "NTE_BAD_SIGNATURE: Invalid Signature.")// NTE_BAD_SIGNATURE
        ERR(0x80090007L, "NTE_BAD_VER: Bad Version of provider.")// NTE_BAD_VER
        ERR(0x80090008L, "NTE_BAD_ALGID: Invalid algorithm specified.")// NTE_BAD_ALGID
        ERR(0x80090009L, "NTE_BAD_FLAGS: Invalid flags specified.")// NTE_BAD_FLAGS
        ERR(0x8009000AL, "NTE_BAD_TYPE: Invalid type specified.")// NTE_BAD_TYPE
        ERR(0x8009000BL, "NTE_BAD_KEY_STATE: Key not valid for use in specified state.")// NTE_BAD_KEY_STATE
        ERR(0x8009000CL, "NTE_BAD_HASH_STATE: Hash not valid for use in specified state.")// NTE_BAD_HASH_STATE
        ERR(0x8009000DL, "NTE_NO_KEY: Key does not exist.")// NTE_NO_KEY
        ERR(0x8009000EL, "NTE_NO_MEMORY: Insufficient memory available for the operation.")// NTE_NO_MEMORY
        ERR(0x8009000FL, "NTE_EXISTS: Object already exists.")// NTE_EXISTS
        ERR(0x80090010L, "NTE_PERM: Access denied.")// NTE_PERM
        ERR(0x80090011L, "NTE_NOT_FOUND: Object was not found.")// NTE_NOT_FOUND
        ERR(0x80090012L, "NTE_DOUBLE_ENCRYPT: Data already encrypted.")// NTE_DOUBLE_ENCRYPT
        ERR(0x80090013L, "NTE_BAD_PROVIDER: Invalid provider specified.")// NTE_BAD_PROVIDER
        ERR(0x80090014L, "NTE_BAD_PROV_TYPE: Invalid provider type specified.")// NTE_BAD_PROV_TYPE
        ERR(0x80090015L, "NTE_BAD_PUBLIC_KEY: Provider's public key is invalid.")// NTE_BAD_PUBLIC_KEY
        ERR(0x80090016L, "NTE_BAD_KEYSET: Keyset does not exist")// NTE_BAD_KEYSET
        ERR(0x80090017L, "NTE_PROV_TYPE_NOT_DEF: Provider type not defined.")// NTE_PROV_TYPE_NOT_DEF
        ERR(0x80090018L, "NTE_PROV_TYPE_ENTRY_BAD: Provider type as registered is invalid.")// NTE_PROV_TYPE_ENTRY_BAD
        ERR(0x80090019L, "NTE_KEYSET_NOT_DEF: The keyset is not defined.")// NTE_KEYSET_NOT_DEF
        ERR(0x8009001AL, "NTE_KEYSET_ENTRY_BAD: Keyset as registered is invalid.")// NTE_KEYSET_ENTRY_BAD
        ERR(0x8009001BL, "NTE_PROV_TYPE_NO_MATCH: Provider type does not match registered value.")// NTE_PROV_TYPE_NO_MATCH
        ERR(0x8009001CL, "NTE_SIGNATURE_FILE_BAD: The digital signature file is corrupt.")// NTE_SIGNATURE_FILE_BAD
        ERR(0x8009001DL, "NTE_PROVIDER_DLL_FAIL: Provider DLL failed to initialize correctly.")// NTE_PROVIDER_DLL_FAIL
        ERR(0x8009001EL, "NTE_PROV_DLL_NOT_FOUND: Provider DLL could not be found.")// NTE_PROV_DLL_NOT_FOUND
        ERR(0x8009001FL, "NTE_BAD_KEYSET_PARAM: The Keyset parameter is invalid.")// NTE_BAD_KEYSET_PARAM
        ERR(0x80090020L, "NTE_FAIL: An internal error occurred.")// NTE_FAIL
        ERR(0x80090021L, "NTE_SYS_ERR: A base error occurred.")// NTE_SYS_ERR
        ERR(0x80090022L, "NTE_SILENT_CONTEXT: Provider could not perform the action since the context was acquired as silent.")// NTE_SILENT_CONTEXT
        ERR(0x80090023L, "NTE_TOKEN_KEYSET_STORAGE_FULL: The security token does not have storage space available for an additional container.")// NTE_TOKEN_KEYSET_STORAGE_FULL
        ERR(0x80090024L, "NTE_TEMPORARY_PROFILE: The profile for the user is a temporary profile.")// NTE_TEMPORARY_PROFILE
        ERR(0x80090025L, "NTE_FIXEDPARAMETER: The key parameters could not be set because the CSP uses fixed parameters.")// NTE_FIXEDPARAMETER
        ERR(0x80090300L, "SEC_E_INSUFFICIENT_MEMORY: Not enough memory is available to complete this request")// SEC_E_INSUFFICIENT_MEMORY
        ERR(0x80090301L, "SEC_E_INVALID_HANDLE: The handle specified is invalid")// SEC_E_INVALID_HANDLE
        ERR(0x80090302L, "SEC_E_UNSUPPORTED_FUNCTION: The function requested is not supported")// SEC_E_UNSUPPORTED_FUNCTION
        ERR(0x80090303L, "SEC_E_TARGET_UNKNOWN: The specified target is unknown or unreachable")// SEC_E_TARGET_UNKNOWN
        ERR(0x80090304L, "SEC_E_INTERNAL_ERROR: The Local Security Authority cannot be contacted")// SEC_E_INTERNAL_ERROR
        ERR(0x80090305L, "SEC_E_SECPKG_NOT_FOUND: The requested security package does not exist")// SEC_E_SECPKG_NOT_FOUND
        ERR(0x80090306L, "SEC_E_NOT_OWNER: The caller is not the owner of the desired credentials")// SEC_E_NOT_OWNER
        ERR(0x80090307L, "SEC_E_CANNOT_INSTALL: The security package failed to initialize, and cannot be installed")// SEC_E_CANNOT_INSTALL
        ERR(0x80090308L, "SEC_E_INVALID_TOKEN: The token supplied to the function is invalid")// SEC_E_INVALID_TOKEN
        ERR(0x80090309L, "SEC_E_CANNOT_PACK: The security package is not able to marshall the logon buffer, so the logon attempt has failed")// SEC_E_CANNOT_PACK
        ERR(0x8009030AL, "SEC_E_QOP_NOT_SUPPORTED: The per-message Quality of Protection is not supported by the security package")// SEC_E_QOP_NOT_SUPPORTED
        ERR(0x8009030BL, "SEC_E_NO_IMPERSONATION: The security context does not allow impersonation of the client")// SEC_E_NO_IMPERSONATION
        ERR(0x8009030CL, "SEC_E_LOGON_DENIED: The logon attempt failed")// SEC_E_LOGON_DENIED
        ERR(0x8009030DL, "SEC_E_UNKNOWN_CREDENTIALS: The credentials supplied to the package were not recognized")// SEC_E_UNKNOWN_CREDENTIALS
        ERR(0x8009030EL, "SEC_E_NO_CREDENTIALS: No credentials are available in the security package")// SEC_E_NO_CREDENTIALS
        ERR(0x8009030FL, "SEC_E_MESSAGE_ALTERED: The message or signature supplied for verification has been altered")// SEC_E_MESSAGE_ALTERED
        ERR(0x80090310L, "SEC_E_OUT_OF_SEQUENCE: The message supplied for verification is out of sequence")// SEC_E_OUT_OF_SEQUENCE
        ERR(0x80090311L, "SEC_E_NO_AUTHENTICATING_AUTHORITY: No authority could be contacted for authentication.")// SEC_E_NO_AUTHENTICATING_AUTHORITY
        ERR(0x00090312L, "SEC_I_CONTINUE_NEEDED: The function completed successfully, but must be called again to complete the context")// SEC_I_CONTINUE_NEEDED
        ERR(0x00090313L, "SEC_I_COMPLETE_NEEDED: The function completed successfully, but CompleteToken must be called")// SEC_I_COMPLETE_NEEDED
        ERR(0x00090314L, "SEC_I_COMPLETE_AND_CONTINUE: The function completed successfully, but both CompleteToken and this function must be called to complete the context")// SEC_I_COMPLETE_AND_CONTINUE
        ERR(0x00090315L, "SEC_I_LOCAL_LOGON: The logon was completed, but no network authority was available. The logon was made using locally known information")// SEC_I_LOCAL_LOGON
        ERR(0x80090316L, "SEC_E_BAD_PKGID: The requested security package does not exist")// SEC_E_BAD_PKGID
        ERR(0x80090317L, "SEC_E_CONTEXT_EXPIRED: The context has expired and can no longer be used.")// SEC_E_CONTEXT_EXPIRED
        ERR(0x80090318L, "SEC_E_INCOMPLETE_MESSAGE: The supplied message is incomplete. The signature was not verified.")// SEC_E_INCOMPLETE_MESSAGE
        ERR(0x80090320L, "SEC_E_INCOMPLETE_CREDENTIALS: The credentials supplied were not complete, and could not be verified. The context could not be initialized.")// SEC_E_INCOMPLETE_CREDENTIALS
        ERR(0x80090321L, "SEC_E_BUFFER_TOO_SMALL: The buffers supplied to a function was too small.")// SEC_E_BUFFER_TOO_SMALL
        ERR(0x00090320L, "SEC_I_INCOMPLETE_CREDENTIALS: The credentials supplied were not complete, and could not be verified. Additional information can be returned from the context.")// SEC_I_INCOMPLETE_CREDENTIALS
        ERR(0x00090321L, "SEC_I_RENEGOTIATE: The context data must be renegotiated with the peer.")// SEC_I_RENEGOTIATE
        ERR(0x80090322L, "SEC_E_WRONG_PRINCIPAL: The target principal name is incorrect.")// SEC_E_WRONG_PRINCIPAL
        ERR(0x00090323L, "SEC_I_NO_LSA_CONTEXT: There is no LSA mode context associated with this context.")// SEC_I_NO_LSA_CONTEXT
        ERR(0x80090324L, "SEC_E_TIME_SKEW: The clocks on the client and server machines are skewed.")// SEC_E_TIME_SKEW
        ERR(0x80090325L, "SEC_E_UNTRUSTED_ROOT: The certificate chain was issued by an untrusted authority.")// SEC_E_UNTRUSTED_ROOT
        ERR(0x80090326L, "SEC_E_ILLEGAL_MESSAGE: The message received was unexpected or badly formatted.")// SEC_E_ILLEGAL_MESSAGE
        ERR(0x80090327L, "SEC_E_CERT_UNKNOWN: An unknown error occurred while processing the certificate.")// SEC_E_CERT_UNKNOWN
        ERR(0x80090328L, "SEC_E_CERT_EXPIRED: The received certificate has expired.")// SEC_E_CERT_EXPIRED
        ERR(0x80090329L, "SEC_E_ENCRYPT_FAILURE: The specified data could not be encrypted.")// SEC_E_ENCRYPT_FAILURE
        ERR(0x80090330L, "SEC_E_DECRYPT_FAILURE: The specified data could not be decrypted.")// SEC_E_DECRYPT_FAILURE
        ERR(0x80090331L, "SEC_E_ALGORITHM_MISMATCH: The client and server cannot communicate, because they do not possess a common algorithm.")// SEC_E_ALGORITHM_MISMATCH
        ERR(0x80090332L, "SEC_E_SECURITY_QOS_FAILED: The security context could not be established due to a failure in the requested quality of service (e.g. mutual authentication or delegation).")// SEC_E_SECURITY_QOS_FAILED
        ERR(0x80090333L, "SEC_E_UNFINISHED_CONTEXT_DELETED: A security context was deleted before the context was completed. This is considered a logon failure.")// SEC_E_UNFINISHED_CONTEXT_DELETED
        ERR(0x80090334L, "SEC_E_NO_TGT_REPLY: The client is trying to negotiate a context and the server requires user-to-user but didn't send a TGT reply.")// SEC_E_NO_TGT_REPLY
        ERR(0x80090335L, "SEC_E_NO_IP_ADDRESSES: Unable to accomplish the requested task because the local machine does not have any IP addresses.")// SEC_E_NO_IP_ADDRESSES
        ERR(0x80090336L, "SEC_E_WRONG_CREDENTIAL_HANDLE: The supplied credential handle does not match the credential associated with the security context.")// SEC_E_WRONG_CREDENTIAL_HANDLE
        ERR(0x80090337L, "SEC_E_CRYPTO_SYSTEM_INVALID: The crypto system or checksum function is invalid because a required function is unavailable.")// SEC_E_CRYPTO_SYSTEM_INVALID
        ERR(0x80090338L, "SEC_E_MAX_REFERRALS_EXCEEDED: The number of maximum ticket referrals has been exceeded.")// SEC_E_MAX_REFERRALS_EXCEEDED
        ERR(0x80090339L, "SEC_E_MUST_BE_KDC: The local machine must be a Kerberos KDC (domain controller) and it is not.")// SEC_E_MUST_BE_KDC
        ERR(0x8009033AL, "SEC_E_STRONG_CRYPTO_NOT_SUPPORTED: The other end of the security negotiation is requires strong crypto but it is not supported on the local machine.")// SEC_E_STRONG_CRYPTO_NOT_SUPPORTED
        ERR(0x8009033BL, "SEC_E_TOO_MANY_PRINCIPALS: The KDC reply contained more than one principal name.")// SEC_E_TOO_MANY_PRINCIPALS
        ERR(0x8009033CL, "SEC_E_NO_PA_DATA: Expected to find PA data for a hint of what etype to use, but it was not found.")// SEC_E_NO_PA_DATA
        ERR(0x8009033DL, "SEC_E_PKINIT_NAME_MISMATCH: The client cert name does not matches the user name or the KDC name is incorrect.")// SEC_E_PKINIT_NAME_MISMATCH
        ERR(0x8009033EL, "SEC_E_SMARTCARD_LOGON_REQUIRED: Smartcard logon is required and was not used.")// SEC_E_SMARTCARD_LOGON_REQUIRED
        ERR(0x8009033FL, "SEC_E_SHUTDOWN_IN_PROGRESS: A system shutdown is in progress.")// SEC_E_SHUTDOWN_IN_PROGRESS
        ERR(0x80090340L, "SEC_E_KDC_INVALID_REQUEST: An invalid request was sent to the KDC.")// SEC_E_KDC_INVALID_REQUEST
        ERR(0x80090341L, "SEC_E_KDC_UNABLE_TO_REFER: The KDC was unable to generate a referral for the service requested.")// SEC_E_KDC_UNABLE_TO_REFER
        ERR(0x80090342L, "SEC_E_KDC_UNKNOWN_ETYPE: The encryption type requested is not supported by the KDC.")// SEC_E_KDC_UNKNOWN_ETYPE
        ERR(0x80090343L, "SEC_E_UNSUPPORTED_PREAUTH: An unsupported preauthentication mechanism was presented to the kerberos package.")// SEC_E_UNSUPPORTED_PREAUTH
        ERR(0x00090344L, "SEC_I_CONTEXT_EXPIRED: The context has expired and can no longer be used.")// SEC_I_CONTEXT_EXPIRED
        ERR(0x80090345L, "SEC_E_DELEGATION_REQUIRED: The requested operation requires delegation to be enabled on the machine.")// SEC_E_DELEGATION_REQUIRED
        ERR(0x80091001L, "CRYPT_E_MSG_ERROR: An error occurred while performing an operation on a cryptographic message.")// CRYPT_E_MSG_ERROR
        ERR(0x80091002L, "CRYPT_E_UNKNOWN_ALGO: Unknown cryptographic algorithm.")// CRYPT_E_UNKNOWN_ALGO
        ERR(0x80091003L, "CRYPT_E_OID_FORMAT: The object identifier is poorly formatted.")// CRYPT_E_OID_FORMAT
        ERR(0x80091004L, "CRYPT_E_INVALID_MSG_TYPE: Invalid cryptographic message type.")// CRYPT_E_INVALID_MSG_TYPE
        ERR(0x80091005L, "CRYPT_E_UNEXPECTED_ENCODING: Unexpected cryptographic message encoding.")// CRYPT_E_UNEXPECTED_ENCODING
        ERR(0x80091006L, "CRYPT_E_AUTH_ATTR_MISSING: The cryptographic message does not contain an expected authenticated attribute.")// CRYPT_E_AUTH_ATTR_MISSING
        ERR(0x80091007L, "CRYPT_E_HASH_VALUE: The hash value is not correct.")// CRYPT_E_HASH_VALUE
        ERR(0x80091008L, "CRYPT_E_INVALID_INDEX: The index value is not valid.")// CRYPT_E_INVALID_INDEX
        ERR(0x80091009L, "CRYPT_E_ALREADY_DECRYPTED: The content of the cryptographic message has already been decrypted.")// CRYPT_E_ALREADY_DECRYPTED
        ERR(0x8009100AL, "CRYPT_E_NOT_DECRYPTED: The content of the cryptographic message has not been decrypted yet.")// CRYPT_E_NOT_DECRYPTED
        ERR(0x8009100BL, "CRYPT_E_RECIPIENT_NOT_FOUND: The enveloped-data message does not contain the specified recipient.")// CRYPT_E_RECIPIENT_NOT_FOUND
        ERR(0x8009100CL, "CRYPT_E_CONTROL_TYPE: Invalid control type.")// CRYPT_E_CONTROL_TYPE
        ERR(0x8009100DL, "CRYPT_E_ISSUER_SERIALNUMBER: Invalid issuer and/or serial number.")// CRYPT_E_ISSUER_SERIALNUMBER
        ERR(0x8009100EL, "CRYPT_E_SIGNER_NOT_FOUND: Cannot find the original signer.")// CRYPT_E_SIGNER_NOT_FOUND
        ERR(0x8009100FL, "CRYPT_E_ATTRIBUTES_MISSING: The cryptographic message does not contain all of the requested attributes.")// CRYPT_E_ATTRIBUTES_MISSING
        ERR(0x80091010L, "CRYPT_E_STREAM_MSG_NOT_READY: The streamed cryptographic message is not ready to return data.")// CRYPT_E_STREAM_MSG_NOT_READY
        ERR(0x80091011L, "CRYPT_E_STREAM_INSUFFICIENT_DATA: The streamed cryptographic message requires more data to complete the decode operation.")// CRYPT_E_STREAM_INSUFFICIENT_DATA
        ERR(0x00091012L, "CRYPT_I_NEW_PROTECTION_REQUIRED: The protected data needs to be re-protected.")// CRYPT_I_NEW_PROTECTION_REQUIRED
        ERR(0x80092001L, "CRYPT_E_BAD_LEN: The length specified for the output data was insufficient.")// CRYPT_E_BAD_LEN
        ERR(0x80092002L, "CRYPT_E_BAD_ENCODE: An error occurred during encode or decode operation.")// CRYPT_E_BAD_ENCODE
        ERR(0x80092003L, "CRYPT_E_FILE_ERROR: An error occurred while reading or writing to a file.")// CRYPT_E_FILE_ERROR
        ERR(0x80092004L, "CRYPT_E_NOT_FOUND: Cannot find object or property.")// CRYPT_E_NOT_FOUND
        ERR(0x80092005L, "CRYPT_E_EXISTS: The object or property already exists.")// CRYPT_E_EXISTS
        ERR(0x80092006L, "CRYPT_E_NO_PROVIDER: No provider was specified for the store or object.")// CRYPT_E_NO_PROVIDER
        ERR(0x80092007L, "CRYPT_E_SELF_SIGNED: The specified certificate is self signed.")// CRYPT_E_SELF_SIGNED
        ERR(0x80092008L, "CRYPT_E_DELETED_PREV: The previous certificate or CRL context was deleted.")// CRYPT_E_DELETED_PREV
        ERR(0x80092009L, "CRYPT_E_NO_MATCH: Cannot find the requested object.")// CRYPT_E_NO_MATCH
        ERR(0x8009200AL, "CRYPT_E_UNEXPECTED_MSG_TYPE: The certificate does not have a property that references a private key.")// CRYPT_E_UNEXPECTED_MSG_TYPE
        ERR(0x8009200BL, "CRYPT_E_NO_KEY_PROPERTY: Cannot find the certificate and private key for decryption.")// CRYPT_E_NO_KEY_PROPERTY
        ERR(0x8009200CL, "CRYPT_E_NO_DECRYPT_CERT: Cannot find the certificate and private key to use for decryption.")// CRYPT_E_NO_DECRYPT_CERT
        ERR(0x8009200DL, "CRYPT_E_BAD_MSG: Not a cryptographic message or the cryptographic message is not formatted correctly.")// CRYPT_E_BAD_MSG
        ERR(0x8009200EL, "CRYPT_E_NO_SIGNER: The signed cryptographic message does not have a signer for the specified signer index.")// CRYPT_E_NO_SIGNER
        ERR(0x8009200FL, "CRYPT_E_PENDING_CLOSE: Final closure is pending until additional frees or closes.")// CRYPT_E_PENDING_CLOSE
        ERR(0x80092010L, "CRYPT_E_REVOKED: The certificate is revoked.")// CRYPT_E_REVOKED
        ERR(0x80092011L, "CRYPT_E_NO_REVOCATION_DLL: No Dll or exported function was found to verify revocation.")// CRYPT_E_NO_REVOCATION_DLL
        ERR(0x80092012L, "CRYPT_E_NO_REVOCATION_CHECK: The revocation function was unable to check revocation for the certificate.")// CRYPT_E_NO_REVOCATION_CHECK
        ERR(0x80092013L, "CRYPT_E_REVOCATION_OFFLINE: The revocation function was unable to check revocation because the revocation server was offline.")// CRYPT_E_REVOCATION_OFFLINE
        ERR(0x80092014L, "CRYPT_E_NOT_IN_REVOCATION_DATABASE: The certificate is not in the revocation server's database.")// CRYPT_E_NOT_IN_REVOCATION_DATABASE
        ERR(0x80092020L, "CRYPT_E_INVALID_NUMERIC_STRING: The string contains a non-numeric character.")// CRYPT_E_INVALID_NUMERIC_STRING
        ERR(0x80092021L, "CRYPT_E_INVALID_PRINTABLE_STRING: The string contains a non-printable character.")// CRYPT_E_INVALID_PRINTABLE_STRING
        ERR(0x80092022L, "CRYPT_E_INVALID_IA5_STRING: The string contains a character not in the 7 bit ASCII character set.")// CRYPT_E_INVALID_IA5_STRING
        ERR(0x80092023L, "CRYPT_E_INVALID_X500_STRING: The string contains an invalid X500 name attribute key, oid, value or delimiter.")// CRYPT_E_INVALID_X500_STRING
        ERR(0x80092024L, "CRYPT_E_NOT_CHAR_STRING: The dwValueType for the CERT_NAME_VALUE is not one of the character strings. Most likely it is either a CERT_RDN_ENCODED_BLOB or CERT_TDN_OCTED_STRING.")// CRYPT_E_NOT_CHAR_STRING
        ERR(0x80092025L, "CRYPT_E_FILERESIZED: The Put operation can not continue. The file needs to be resized. However, there is already a signature present. A complete signing operation must be done.")// CRYPT_E_FILERESIZED
        ERR(0x80092026L, "CRYPT_E_SECURITY_SETTINGS: The cryptographic operation failed due to a local security option setting.")// CRYPT_E_SECURITY_SETTINGS
        ERR(0x80092027L, "CRYPT_E_NO_VERIFY_USAGE_DLL: No DLL or exported function was found to verify subject usage.")// CRYPT_E_NO_VERIFY_USAGE_DLL
        ERR(0x80092028L, "CRYPT_E_NO_VERIFY_USAGE_CHECK: The called function was unable to do a usage check on the subject.")// CRYPT_E_NO_VERIFY_USAGE_CHECK
        ERR(0x80092029L, "CRYPT_E_VERIFY_USAGE_OFFLINE: Since the server was offline, the called function was unable to complete the usage check.")// CRYPT_E_VERIFY_USAGE_OFFLINE
        ERR(0x8009202AL, "CRYPT_E_NOT_IN_CTL: The subject was not found in a Certificate Trust List (CTL).")// CRYPT_E_NOT_IN_CTL
        ERR(0x8009202BL, "CRYPT_E_NO_TRUSTED_SIGNER: None of the signers of the cryptographic message or certificate trust list is trusted.")// CRYPT_E_NO_TRUSTED_SIGNER
        ERR(0x8009202CL, "CRYPT_E_MISSING_PUBKEY_PARA: The public key's algorithm parameters are missing.")// CRYPT_E_MISSING_PUBKEY_PARA
        ERR(0x80093000L, "CRYPT_E_OSS_ERROR: OSS Certificate encode/decode error code base")// CRYPT_E_OSS_ERROR
        ERR(0x80093001L, "OSS_MORE_BUF: OSS ASN.1 Error: Output Buffer is too small.")// OSS_MORE_BUF
        ERR(0x80093002L, "OSS_NEGATIVE_UINTEGER: OSS ASN.1 Error: Signed integer is encoded as a unsigned integer.")// OSS_NEGATIVE_UINTEGER
        ERR(0x80093003L, "OSS_PDU_RANGE: OSS ASN.1 Error: Unknown ASN.1 data type.")// OSS_PDU_RANGE
        ERR(0x80093004L, "OSS_MORE_INPUT: OSS ASN.1 Error: Output buffer is too small, the decoded data has been truncated.")// OSS_MORE_INPUT
        ERR(0x80093005L, "OSS_DATA_ERROR: OSS ASN.1 Error: Invalid data.")// OSS_DATA_ERROR
        ERR(0x80093006L, "OSS_BAD_ARG: OSS ASN.1 Error: Invalid argument.")// OSS_BAD_ARG
        ERR(0x80093007L, "OSS_BAD_VERSION: OSS ASN.1 Error: Encode/Decode version mismatch.")// OSS_BAD_VERSION
        ERR(0x80093008L, "OSS_OUT_MEMORY: OSS ASN.1 Error: Out of memory.")// OSS_OUT_MEMORY
        ERR(0x80093009L, "OSS_PDU_MISMATCH: OSS ASN.1 Error: Encode/Decode Error.")// OSS_PDU_MISMATCH
        ERR(0x8009300AL, "OSS_LIMITED: OSS ASN.1 Error: Internal Error.")// OSS_LIMITED
        ERR(0x8009300BL, "OSS_BAD_PTR: OSS ASN.1 Error: Invalid data.")// OSS_BAD_PTR
        ERR(0x8009300CL, "OSS_BAD_TIME: OSS ASN.1 Error: Invalid data.")// OSS_BAD_TIME
        ERR(0x8009300DL, "OSS_INDEFINITE_NOT_SUPPORTED: OSS ASN.1 Error: Unsupported BER indefinite-length encoding.")// OSS_INDEFINITE_NOT_SUPPORTED
        ERR(0x8009300EL, "OSS_MEM_ERROR: OSS ASN.1 Error: Access violation.")// OSS_MEM_ERROR
        ERR(0x8009300FL, "OSS_BAD_TABLE: OSS ASN.1 Error: Invalid data.")// OSS_BAD_TABLE
        ERR(0x80093010L, "OSS_TOO_LONG: OSS ASN.1 Error: Invalid data.")// OSS_TOO_LONG
        ERR(0x80093011L, "OSS_CONSTRAINT_VIOLATED: OSS ASN.1 Error: Invalid data.")// OSS_CONSTRAINT_VIOLATED
        ERR(0x80093012L, "OSS_FATAL_ERROR: OSS ASN.1 Error: Internal Error.")// OSS_FATAL_ERROR
        ERR(0x80093013L, "OSS_ACCESS_SERIALIZATION_ERROR: OSS ASN.1 Error: Multi-threading conflict.")// OSS_ACCESS_SERIALIZATION_ERROR
        ERR(0x80093014L, "OSS_NULL_TBL: OSS ASN.1 Error: Invalid data.")// OSS_NULL_TBL
        ERR(0x80093015L, "OSS_NULL_FCN: OSS ASN.1 Error: Invalid data.")// OSS_NULL_FCN
        ERR(0x80093016L, "OSS_BAD_ENCRULES: OSS ASN.1 Error: Invalid data.")// OSS_BAD_ENCRULES
        ERR(0x80093017L, "OSS_UNAVAIL_ENCRULES: OSS ASN.1 Error: Encode/Decode function not implemented.")// OSS_UNAVAIL_ENCRULES
        ERR(0x80093018L, "OSS_CANT_OPEN_TRACE_WINDOW: OSS ASN.1 Error: Trace file error.")// OSS_CANT_OPEN_TRACE_WINDOW
        ERR(0x80093019L, "OSS_UNIMPLEMENTED: OSS ASN.1 Error: Function not implemented.")// OSS_UNIMPLEMENTED
        ERR(0x8009301AL, "OSS_OID_DLL_NOT_LINKED: OSS ASN.1 Error: Program link error.")// OSS_OID_DLL_NOT_LINKED
        ERR(0x8009301BL, "OSS_CANT_OPEN_TRACE_FILE: OSS ASN.1 Error: Trace file error.")// OSS_CANT_OPEN_TRACE_FILE
        ERR(0x8009301CL, "OSS_TRACE_FILE_ALREADY_OPEN: OSS ASN.1 Error: Trace file error.")// OSS_TRACE_FILE_ALREADY_OPEN
        ERR(0x8009301DL, "OSS_TABLE_MISMATCH: OSS ASN.1 Error: Invalid data.")// OSS_TABLE_MISMATCH
        ERR(0x8009301EL, "OSS_TYPE_NOT_SUPPORTED: OSS ASN.1 Error: Invalid data.")// OSS_TYPE_NOT_SUPPORTED
        ERR(0x8009301FL, "OSS_REAL_DLL_NOT_LINKED: OSS ASN.1 Error: Program link error.")// OSS_REAL_DLL_NOT_LINKED
        ERR(0x80093020L, "OSS_REAL_CODE_NOT_LINKED: OSS ASN.1 Error: Program link error.")// OSS_REAL_CODE_NOT_LINKED
        ERR(0x80093021L, "OSS_OUT_OF_RANGE: OSS ASN.1 Error: Program link error.")// OSS_OUT_OF_RANGE
        ERR(0x80093022L, "OSS_COPIER_DLL_NOT_LINKED: OSS ASN.1 Error: Program link error.")// OSS_COPIER_DLL_NOT_LINKED
        ERR(0x80093023L, "OSS_CONSTRAINT_DLL_NOT_LINKED: OSS ASN.1 Error: Program link error.")// OSS_CONSTRAINT_DLL_NOT_LINKED
        ERR(0x80093024L, "OSS_COMPARATOR_DLL_NOT_LINKED: OSS ASN.1 Error: Program link error.")// OSS_COMPARATOR_DLL_NOT_LINKED
        ERR(0x80093025L, "OSS_COMPARATOR_CODE_NOT_LINKED: OSS ASN.1 Error: Program link error.")// OSS_COMPARATOR_CODE_NOT_LINKED
        ERR(0x80093026L, "OSS_MEM_MGR_DLL_NOT_LINKED: OSS ASN.1 Error: Program link error.")// OSS_MEM_MGR_DLL_NOT_LINKED
        ERR(0x80093027L, "OSS_PDV_DLL_NOT_LINKED: OSS ASN.1 Error: Program link error.")// OSS_PDV_DLL_NOT_LINKED
        ERR(0x80093028L, "OSS_PDV_CODE_NOT_LINKED: OSS ASN.1 Error: Program link error.")// OSS_PDV_CODE_NOT_LINKED
        ERR(0x80093029L, "OSS_API_DLL_NOT_LINKED: OSS ASN.1 Error: Program link error.")// OSS_API_DLL_NOT_LINKED
        ERR(0x8009302AL, "OSS_BERDER_DLL_NOT_LINKED: OSS ASN.1 Error: Program link error.")// OSS_BERDER_DLL_NOT_LINKED
        ERR(0x8009302BL, "OSS_PER_DLL_NOT_LINKED: OSS ASN.1 Error: Program link error.")// OSS_PER_DLL_NOT_LINKED
        ERR(0x8009302CL, "OSS_OPEN_TYPE_ERROR: OSS ASN.1 Error: Program link error.")// OSS_OPEN_TYPE_ERROR
        ERR(0x8009302DL, "OSS_MUTEX_NOT_CREATED: OSS ASN.1 Error: System resource error.")// OSS_MUTEX_NOT_CREATED
        ERR(0x8009302EL, "OSS_CANT_CLOSE_TRACE_FILE: OSS ASN.1 Error: Trace file error.")// OSS_CANT_CLOSE_TRACE_FILE
        ERR(0x80093100L, "CRYPT_E_ASN1_ERROR: ASN1 Certificate encode/decode error code base.")// CRYPT_E_ASN1_ERROR
        ERR(0x80093101L, "CRYPT_E_ASN1_INTERNAL: ASN1 internal encode or decode error.")// CRYPT_E_ASN1_INTERNAL
        ERR(0x80093102L, "CRYPT_E_ASN1_EOD: ASN1 unexpected end of data.")// CRYPT_E_ASN1_EOD
        ERR(0x80093103L, "CRYPT_E_ASN1_CORRUPT: ASN1 corrupted data.")// CRYPT_E_ASN1_CORRUPT
        ERR(0x80093104L, "CRYPT_E_ASN1_LARGE: ASN1 value too large.")// CRYPT_E_ASN1_LARGE
        ERR(0x80093105L, "CRYPT_E_ASN1_CONSTRAINT: ASN1 constraint violated.")// CRYPT_E_ASN1_CONSTRAINT
        ERR(0x80093106L, "CRYPT_E_ASN1_MEMORY: ASN1 out of memory.")// CRYPT_E_ASN1_MEMORY
        ERR(0x80093107L, "CRYPT_E_ASN1_OVERFLOW: ASN1 buffer overflow.")// CRYPT_E_ASN1_OVERFLOW
        ERR(0x80093108L, "CRYPT_E_ASN1_BADPDU: ASN1 function not supported for this PDU.")// CRYPT_E_ASN1_BADPDU
        ERR(0x80093109L, "CRYPT_E_ASN1_BADARGS: ASN1 bad arguments to function call.")// CRYPT_E_ASN1_BADARGS
        ERR(0x8009310AL, "CRYPT_E_ASN1_BADREAL: ASN1 bad real value.")// CRYPT_E_ASN1_BADREAL
        ERR(0x8009310BL, "CRYPT_E_ASN1_BADTAG: ASN1 bad tag value met.")// CRYPT_E_ASN1_BADTAG
        ERR(0x8009310CL, "CRYPT_E_ASN1_CHOICE: ASN1 bad choice value.")// CRYPT_E_ASN1_CHOICE
        ERR(0x8009310DL, "CRYPT_E_ASN1_RULE: ASN1 bad encoding rule.")// CRYPT_E_ASN1_RULE
        ERR(0x8009310EL, "CRYPT_E_ASN1_UTF8: ASN1 bad unicode (UTF8).")// CRYPT_E_ASN1_UTF8
        ERR(0x80093133L, "CRYPT_E_ASN1_PDU_TYPE: ASN1 bad PDU type.")// CRYPT_E_ASN1_PDU_TYPE
        ERR(0x80093134L, "CRYPT_E_ASN1_NYI: ASN1 not yet implemented.")// CRYPT_E_ASN1_NYI
        ERR(0x80093201L, "CRYPT_E_ASN1_EXTENDED: ASN1 skipped unknown extension(s).")// CRYPT_E_ASN1_EXTENDED
        ERR(0x80093202L, "CRYPT_E_ASN1_NOEOD: ASN1 end of data expected")// CRYPT_E_ASN1_NOEOD
        ERR(0x80094001L, "CERTSRV_E_BAD_REQUESTSUBJECT: The request subject name is invalid or too long.")// CERTSRV_E_BAD_REQUESTSUBJECT
        ERR(0x80094002L, "CERTSRV_E_NO_REQUEST: The request does not exist.")// CERTSRV_E_NO_REQUEST
        ERR(0x80094003L, "CERTSRV_E_BAD_REQUESTSTATUS: The request's current status does not allow this operation.")// CERTSRV_E_BAD_REQUESTSTATUS
        ERR(0x80094004L, "CERTSRV_E_PROPERTY_EMPTY: The requested property value is empty.")// CERTSRV_E_PROPERTY_EMPTY
        ERR(0x80094005L, "CERTSRV_E_INVALID_CA_CERTIFICATE: The certification authority's certificate contains invalid data.")// CERTSRV_E_INVALID_CA_CERTIFICATE
        ERR(0x80094006L, "CERTSRV_E_SERVER_SUSPENDED: Certificate service has been suspended for a database restore operation.")// CERTSRV_E_SERVER_SUSPENDED
        ERR(0x80094007L, "CERTSRV_E_ENCODING_LENGTH: The certificate contains an encoded length that is potentially incompatible with older enrollment software.")// CERTSRV_E_ENCODING_LENGTH
        ERR(0x80094800L, "CERTSRV_E_UNSUPPORTED_CERT_TYPE: The requested certificate template is not supported by this CA.")// CERTSRV_E_UNSUPPORTED_CERT_TYPE
        ERR(0x80094801L, "CERTSRV_E_NO_CERT_TYPE: The request contains no certificate template information.")// CERTSRV_E_NO_CERT_TYPE
        ERR(0x80096001L, "TRUST_E_SYSTEM_ERROR: A system-level error occurred while verifying trust.")// TRUST_E_SYSTEM_ERROR
        ERR(0x80096002L, "TRUST_E_NO_SIGNER_CERT: The certificate for the signer of the message is invalid or not found.")// TRUST_E_NO_SIGNER_CERT
        ERR(0x80096003L, "TRUST_E_COUNTER_SIGNER: One of the counter signatures was invalid.")// TRUST_E_COUNTER_SIGNER
        ERR(0x80096004L, "TRUST_E_CERT_SIGNATURE: The signature of the certificate can not be verified.")// TRUST_E_CERT_SIGNATURE
        ERR(0x80096005L, "TRUST_E_TIME_STAMP: The timestamp signature and/or certificate could not be verified or is malformed.")// TRUST_E_TIME_STAMP
        ERR(0x80096010L, "TRUST_E_BAD_DIGEST: The digital signature of the object did not verify.")// TRUST_E_BAD_DIGEST
        ERR(0x80096019L, "TRUST_E_BASIC_CONSTRAINTS: A certificate's basic constraint extension has not been observed.")// TRUST_E_BASIC_CONSTRAINTS
        ERR(0x8009601EL, "TRUST_E_FINANCIAL_CRITERIA: The certificate does not meet or contain the Authenticode financial extensions.")// TRUST_E_FINANCIAL_CRITERIA
        ERR(0x80097001L, "MSSIPOTF_E_OUTOFMEMRANGE: Tried to reference a part of the file outside the proper range.")// MSSIPOTF_E_OUTOFMEMRANGE
        ERR(0x80097002L, "MSSIPOTF_E_CANTGETOBJECT: Could not retrieve an object from the file.")// MSSIPOTF_E_CANTGETOBJECT
        ERR(0x80097003L, "MSSIPOTF_E_NOHEADTABLE: Could not find the head table in the file.")// MSSIPOTF_E_NOHEADTABLE
        ERR(0x80097004L, "MSSIPOTF_E_BAD_MAGICNUMBER: The magic number in the head table is incorrect.")// MSSIPOTF_E_BAD_MAGICNUMBER
        ERR(0x80097005L, "MSSIPOTF_E_BAD_OFFSET_TABLE: The offset table has incorrect values.")// MSSIPOTF_E_BAD_OFFSET_TABLE
        ERR(0x80097006L, "MSSIPOTF_E_TABLE_TAGORDER: Duplicate table tags or tags out of alphabetical order.")// MSSIPOTF_E_TABLE_TAGORDER
        ERR(0x80097007L, "MSSIPOTF_E_TABLE_LONGWORD: A table does not start on a long word boundary.")// MSSIPOTF_E_TABLE_LONGWORD
        ERR(0x80097008L, "MSSIPOTF_E_BAD_FIRST_TABLE_PLACEMENT: First table does not appear after header information.")// MSSIPOTF_E_BAD_FIRST_TABLE_PLACEMENT
        ERR(0x80097009L, "MSSIPOTF_E_TABLES_OVERLAP: Two or more tables overlap.")// MSSIPOTF_E_TABLES_OVERLAP
        ERR(0x8009700AL, "MSSIPOTF_E_TABLE_PADBYTES: Too many pad bytes between tables or pad bytes are not 0.")// MSSIPOTF_E_TABLE_PADBYTES
        ERR(0x8009700BL, "MSSIPOTF_E_FILETOOSMALL: File is too small to contain the last table.")// MSSIPOTF_E_FILETOOSMALL
        ERR(0x8009700CL, "MSSIPOTF_E_TABLE_CHECKSUM: A table checksum is incorrect.")// MSSIPOTF_E_TABLE_CHECKSUM
        ERR(0x8009700DL, "MSSIPOTF_E_FILE_CHECKSUM: The file checksum is incorrect.")// MSSIPOTF_E_FILE_CHECKSUM
        ERR(0x80097010L, "MSSIPOTF_E_FAILED_POLICY: The signature does not have the correct attributes for the policy.")// MSSIPOTF_E_FAILED_POLICY
        ERR(0x80097011L, "MSSIPOTF_E_FAILED_HINTS_CHECK: The file did not pass the hints check.")// MSSIPOTF_E_FAILED_HINTS_CHECK
        ERR(0x80097012L, "MSSIPOTF_E_NOT_OPENTYPE: The file is not an OpenType file.")// MSSIPOTF_E_NOT_OPENTYPE
        ERR(0x80097013L, "MSSIPOTF_E_FILE: Failed on a file operation (open, map, read, write).")// MSSIPOTF_E_FILE
        ERR(0x80097014L, "MSSIPOTF_E_CRYPT: A call to a CryptoAPI function failed.")// MSSIPOTF_E_CRYPT
        ERR(0x80097015L, "MSSIPOTF_E_BADVERSION: There is a bad version number in the file.")// MSSIPOTF_E_BADVERSION
        ERR(0x80097016L, "MSSIPOTF_E_DSIG_STRUCTURE: The structure of the DSIG table is incorrect.")// MSSIPOTF_E_DSIG_STRUCTURE
        ERR(0x80097017L, "MSSIPOTF_E_PCONST_CHECK: A check failed in a partially constant table.")// MSSIPOTF_E_PCONST_CHECK
        ERR(0x80097018L, "MSSIPOTF_E_STRUCTURE: Some kind of structural error.")// MSSIPOTF_E_STRUCTURE
        ERR(0x800B0001L, "TRUST_E_PROVIDER_UNKNOWN: Unknown trust provider.")// TRUST_E_PROVIDER_UNKNOWN
        ERR(0x800B0002L, "TRUST_E_ACTION_UNKNOWN: The trust verification action specified is not supported by the specified trust provider.")// TRUST_E_ACTION_UNKNOWN
        ERR(0x800B0003L, "TRUST_E_SUBJECT_FORM_UNKNOWN: The form specified for the subject is not one supported or known by the specified trust provider.")// TRUST_E_SUBJECT_FORM_UNKNOWN
        ERR(0x800B0004L, "TRUST_E_SUBJECT_NOT_TRUSTED: The subject is not trusted for the specified action.")// TRUST_E_SUBJECT_NOT_TRUSTED
        ERR(0x800B0005L, "DIGSIG_E_ENCODE: Error due to problem in ASN.1 encoding process.")// DIGSIG_E_ENCODE
        ERR(0x800B0006L, "DIGSIG_E_DECODE: Error due to problem in ASN.1 decoding process.")// DIGSIG_E_DECODE
        ERR(0x800B0007L, "DIGSIG_E_EXTENSIBILITY: Reading / writing Extensions where Attributes are appropriate, and visa versa.")// DIGSIG_E_EXTENSIBILITY
        ERR(0x800B0008L, "DIGSIG_E_CRYPTO: Unspecified cryptographic failure.")// DIGSIG_E_CRYPTO
        ERR(0x800B0009L, "PERSIST_E_SIZEDEFINITE: The size of the data could not be determined.")// PERSIST_E_SIZEDEFINITE
        ERR(0x800B000AL, "PERSIST_E_SIZEINDEFINITE: The size of the indefinite-sized data could not be determined.")// PERSIST_E_SIZEINDEFINITE
        ERR(0x800B000BL, "PERSIST_E_NOTSELFSIZING: This object does not read and write self-sizing data.")// PERSIST_E_NOTSELFSIZING
        ERR(0x800B0100L, "TRUST_E_NOSIGNATURE: No signature was present in the subject.")// TRUST_E_NOSIGNATURE
        ERR(0x800B0101L, "CERT_E_EXPIRED: A required certificate is not within its validity period when verifying against the current system clock or the timestamp in the signed file.")// CERT_E_EXPIRED
        ERR(0x800B0102L, "CERT_E_VALIDITYPERIODNESTING: The validity periods of the certification chain do not nest correctly.")// CERT_E_VALIDITYPERIODNESTING
        ERR(0x800B0103L, "CERT_E_ROLE: A certificate that can only be used as an end-entity is being used as a CA or visa versa.")// CERT_E_ROLE
        ERR(0x800B0104L, "CERT_E_PATHLENCONST: A path length constraint in the certification chain has been violated.")// CERT_E_PATHLENCONST
        ERR(0x800B0105L, "CERT_E_CRITICAL: A certificate contains an unknown extension that is marked 'critical'.")// CERT_E_CRITICAL
        ERR(0x800B0106L, "CERT_E_PURPOSE: A certificate being used for a purpose other than the ones specified by its CA.")// CERT_E_PURPOSE
        ERR(0x800B0107L, "CERT_E_ISSUERCHAINING: A parent of a given certificate in fact did not issue that child certificate.")// CERT_E_ISSUERCHAINING
        ERR(0x800B0108L, "CERT_E_MALFORMED: A certificate is missing or has an empty value for an important field, such as a subject or issuer name.")// CERT_E_MALFORMED
        ERR(0x800B0109L, "CERT_E_UNTRUSTEDROOT: A certificate chain processed correctly, but terminated in a root certificate which is not trusted by the trust provider.")// CERT_E_UNTRUSTEDROOT
        ERR(0x800B010AL, "CERT_E_CHAINING: An internal certificate chaining error has occurred.")// CERT_E_CHAINING
        ERR(0x800B010BL, "TRUST_E_FAIL: Generic trust failure.")// TRUST_E_FAIL
        ERR(0x800B010CL, "CERT_E_REVOKED: A certificate was explicitly revoked by its issuer.")// CERT_E_REVOKED
        ERR(0x800B010DL, "CERT_E_UNTRUSTEDTESTROOT: The certification path terminates with the test root which is not trusted with the current policy settings.")// CERT_E_UNTRUSTEDTESTROOT
        ERR(0x800B010EL, "CERT_E_REVOCATION_FAILURE: The revocation process could not continue - the certificate(s) could not be checked.")// CERT_E_REVOCATION_FAILURE
        ERR(0x800B010FL, "CERT_E_CN_NO_MATCH: The certificate's CN name does not match the passed value.")// CERT_E_CN_NO_MATCH
        ERR(0x800B0110L, "CERT_E_WRONG_USAGE: The certificate is not valid for the requested usage.")// CERT_E_WRONG_USAGE
        ERR(0x800B0111L, "TRUST_E_EXPLICIT_DISTRUST: The certificate was explicitly marked as untrusted by the user.")// TRUST_E_EXPLICIT_DISTRUST
        ERR(0x800B0112L, "CERT_E_UNTRUSTEDCA: A certification chain processed correctly, but one of the CA certificates is not trusted by the policy provider.")// CERT_E_UNTRUSTEDCA
        ERR(0x800B0113L, "CERT_E_INVALID_POLICY: The certificate has invalid policy.")// CERT_E_INVALID_POLICY
        ERR(0x800B0114L, "CERT_E_INVALID_NAME: The certificate has an invalid name. The name is not included in the permitted list or is explicitly excluded.")// CERT_E_INVALID_NAME
        ERR(0x800F0000L, "SPAPI_E_EXPECTED_SECTION_NAME: A non-empty line was encountered in the INF before the start of a section.")// SPAPI_E_EXPECTED_SECTION_NAME
        ERR(0x800F0001L, "SPAPI_E_BAD_SECTION_NAME_LINE: A section name marker in the INF is not complete, or does not exist on a line by itself.")// SPAPI_E_BAD_SECTION_NAME_LINE
        ERR(0x800F0002L, "SPAPI_E_SECTION_NAME_TOO_LONG: An INF section was encountered whose name exceeds the maximum section name length.")// SPAPI_E_SECTION_NAME_TOO_LONG
        ERR(0x800F0003L, "SPAPI_E_GENERAL_SYNTAX: The syntax of the INF is invalid.")// SPAPI_E_GENERAL_SYNTAX
        ERR(0x800F0100L, "SPAPI_E_WRONG_INF_STYLE: The style of the INF is different than what was requested.")// SPAPI_E_WRONG_INF_STYLE
        ERR(0x800F0101L, "SPAPI_E_SECTION_NOT_FOUND: The required section was not found in the INF.")// SPAPI_E_SECTION_NOT_FOUND
        ERR(0x800F0102L, "SPAPI_E_LINE_NOT_FOUND: The required line was not found in the INF.")// SPAPI_E_LINE_NOT_FOUND
        ERR(0x800F0103L, "SPAPI_E_NO_BACKUP: The files affected by the installation of this file queue have not been backed up for uninstall.")// SPAPI_E_NO_BACKUP
        ERR(0x800F0200L, "SPAPI_E_NO_ASSOCIATED_CLASS: The INF or the device information set or element does not have an associated install class.")// SPAPI_E_NO_ASSOCIATED_CLASS
        ERR(0x800F0201L, "SPAPI_E_CLASS_MISMATCH: The INF or the device information set or element does not match the specified install class.")// SPAPI_E_CLASS_MISMATCH
        ERR(0x800F0202L, "SPAPI_E_DUPLICATE_FOUND: An existing device was found that is a duplicate of the device being manually installed.")// SPAPI_E_DUPLICATE_FOUND
        ERR(0x800F0203L, "SPAPI_E_NO_DRIVER_SELECTED: There is no driver selected for the device information set or element.")// SPAPI_E_NO_DRIVER_SELECTED
        ERR(0x800F0204L, "SPAPI_E_KEY_DOES_NOT_EXIST: The requested device registry key does not exist.")// SPAPI_E_KEY_DOES_NOT_EXIST
        ERR(0x800F0205L, "SPAPI_E_INVALID_DEVINST_NAME: The device instance name is invalid.")// SPAPI_E_INVALID_DEVINST_NAME
        ERR(0x800F0206L, "SPAPI_E_INVALID_CLASS: The install class is not present or is invalid.")// SPAPI_E_INVALID_CLASS
        ERR(0x800F0207L, "SPAPI_E_DEVINST_ALREADY_EXISTS: The device instance cannot be created because it already exists.")// SPAPI_E_DEVINST_ALREADY_EXISTS
        ERR(0x800F0208L, "SPAPI_E_DEVINFO_NOT_REGISTERED: The operation cannot be performed on a device information element that has not been registered.")// SPAPI_E_DEVINFO_NOT_REGISTERED
        ERR(0x800F0209L, "SPAPI_E_INVALID_REG_PROPERTY: The device property code is invalid.")// SPAPI_E_INVALID_REG_PROPERTY
        ERR(0x800F020AL, "SPAPI_E_NO_INF: The INF from which a driver list is to be built does not exist.")// SPAPI_E_NO_INF
        ERR(0x800F020BL, "SPAPI_E_NO_SUCH_DEVINST: The device instance does not exist in the hardware tree.")// SPAPI_E_NO_SUCH_DEVINST
        ERR(0x800F020CL, "SPAPI_E_CANT_LOAD_CLASS_ICON: The icon representing this install class cannot be loaded.")// SPAPI_E_CANT_LOAD_CLASS_ICON
        ERR(0x800F020DL, "SPAPI_E_INVALID_CLASS_INSTALLER: The class installer registry entry is invalid.")// SPAPI_E_INVALID_CLASS_INSTALLER
        ERR(0x800F020EL, "SPAPI_E_DI_DO_DEFAULT: The class installer has indicated that the default action should be performed for this installation request.")// SPAPI_E_DI_DO_DEFAULT
        ERR(0x800F020FL, "SPAPI_E_DI_NOFILECOPY: The operation does not require any files to be copied.")// SPAPI_E_DI_NOFILECOPY
        ERR(0x800F0210L, "SPAPI_E_INVALID_HWPROFILE: The specified hardware profile does not exist.")// SPAPI_E_INVALID_HWPROFILE
        ERR(0x800F0211L, "SPAPI_E_NO_DEVICE_SELECTED: There is no device information element currently selected for this device information set.")// SPAPI_E_NO_DEVICE_SELECTED
        ERR(0x800F0212L, "SPAPI_E_DEVINFO_LIST_LOCKED: The operation cannot be performed because the device information set is locked.")// SPAPI_E_DEVINFO_LIST_LOCKED
        ERR(0x800F0213L, "SPAPI_E_DEVINFO_DATA_LOCKED: The operation cannot be performed because the device information element is locked.")// SPAPI_E_DEVINFO_DATA_LOCKED
        ERR(0x800F0214L, "SPAPI_E_DI_BAD_PATH: The specified path does not contain any applicable device INFs.")// SPAPI_E_DI_BAD_PATH
        ERR(0x800F0215L, "SPAPI_E_NO_CLASSINSTALL_PARAMS: No class installer parameters have been set for the device information set or element.")// SPAPI_E_NO_CLASSINSTALL_PARAMS
        ERR(0x800F0216L, "SPAPI_E_FILEQUEUE_LOCKED: The operation cannot be performed because the file queue is locked.")// SPAPI_E_FILEQUEUE_LOCKED
        ERR(0x800F0217L, "SPAPI_E_BAD_SERVICE_INSTALLSECT: A service installation section in this INF is invalid.")// SPAPI_E_BAD_SERVICE_INSTALLSECT
        ERR(0x800F0218L, "SPAPI_E_NO_CLASS_DRIVER_LIST: There is no class driver list for the device information element.")// SPAPI_E_NO_CLASS_DRIVER_LIST
        ERR(0x800F0219L, "SPAPI_E_NO_ASSOCIATED_SERVICE: The installation failed because a function driver was not specified for this device instance.")// SPAPI_E_NO_ASSOCIATED_SERVICE
        ERR(0x800F021AL, "SPAPI_E_NO_DEFAULT_DEVICE_INTERFACE: There is presently no default device interface designated for this interface class.")// SPAPI_E_NO_DEFAULT_DEVICE_INTERFACE
        ERR(0x800F021BL, "SPAPI_E_DEVICE_INTERFACE_ACTIVE: The operation cannot be performed because the device interface is currently active.")// SPAPI_E_DEVICE_INTERFACE_ACTIVE
        ERR(0x800F021CL, "SPAPI_E_DEVICE_INTERFACE_REMOVED: The operation cannot be performed because the device interface has been removed from the system.")// SPAPI_E_DEVICE_INTERFACE_REMOVED
        ERR(0x800F021DL, "SPAPI_E_BAD_INTERFACE_INSTALLSECT: An interface installation section in this INF is invalid.")// SPAPI_E_BAD_INTERFACE_INSTALLSECT
        ERR(0x800F021EL, "SPAPI_E_NO_SUCH_INTERFACE_CLASS: This interface class does not exist in the system.")// SPAPI_E_NO_SUCH_INTERFACE_CLASS
        ERR(0x800F021FL, "SPAPI_E_INVALID_REFERENCE_STRING: The reference string supplied for this interface device is invalid.")// SPAPI_E_INVALID_REFERENCE_STRING
        ERR(0x800F0220L, "SPAPI_E_INVALID_MACHINENAME: The specified machine name does not conform to UNC naming conventions.")// SPAPI_E_INVALID_MACHINENAME
        ERR(0x800F0221L, "SPAPI_E_REMOTE_COMM_FAILURE: A general remote communication error occurred.")// SPAPI_E_REMOTE_COMM_FAILURE
        ERR(0x800F0222L, "SPAPI_E_MACHINE_UNAVAILABLE: The machine selected for remote communication is not available at this time.")// SPAPI_E_MACHINE_UNAVAILABLE
        ERR(0x800F0223L, "SPAPI_E_NO_CONFIGMGR_SERVICES: The Plug and Play service is not available on the remote machine.")// SPAPI_E_NO_CONFIGMGR_SERVICES
        ERR(0x800F0224L, "SPAPI_E_INVALID_PROPPAGE_PROVIDER: The property page provider registry entry is invalid.")// SPAPI_E_INVALID_PROPPAGE_PROVIDER
        ERR(0x800F0225L, "SPAPI_E_NO_SUCH_DEVICE_INTERFACE: The requested device interface is not present in the system.")// SPAPI_E_NO_SUCH_DEVICE_INTERFACE
        ERR(0x800F0226L, "SPAPI_E_DI_POSTPROCESSING_REQUIRED: The device's co-installer has additional work to perform after installation is complete.")// SPAPI_E_DI_POSTPROCESSING_REQUIRED
        ERR(0x800F0227L, "SPAPI_E_INVALID_COINSTALLER: The device's co-installer is invalid.")// SPAPI_E_INVALID_COINSTALLER
        ERR(0x800F0228L, "SPAPI_E_NO_COMPAT_DRIVERS: There are no compatible drivers for this device.")// SPAPI_E_NO_COMPAT_DRIVERS
        ERR(0x800F0229L, "SPAPI_E_NO_DEVICE_ICON: There is no icon that represents this device or device type.")// SPAPI_E_NO_DEVICE_ICON
        ERR(0x800F022AL, "SPAPI_E_INVALID_INF_LOGCONFIG: A logical configuration specified in this INF is invalid.")// SPAPI_E_INVALID_INF_LOGCONFIG
        ERR(0x800F022BL, "SPAPI_E_DI_DONT_INSTALL: The class installer has denied the request to install or upgrade this device.")// SPAPI_E_DI_DONT_INSTALL
        ERR(0x800F022CL, "SPAPI_E_INVALID_FILTER_DRIVER: One of the filter drivers installed for this device is invalid.")// SPAPI_E_INVALID_FILTER_DRIVER
        ERR(0x800F022DL, "SPAPI_E_NON_WINDOWS_NT_DRIVER: The driver selected for this device does not support Windows 2000.")// SPAPI_E_NON_WINDOWS_NT_DRIVER
        ERR(0x800F022EL, "SPAPI_E_NON_WINDOWS_DRIVER: The driver selected for this device does not support Windows.")// SPAPI_E_NON_WINDOWS_DRIVER
        ERR(0x800F022FL, "SPAPI_E_NO_CATALOG_FOR_OEM_INF: The third-party INF does not contain digital signature information.")// SPAPI_E_NO_CATALOG_FOR_OEM_INF
        ERR(0x800F0230L, "SPAPI_E_DEVINSTALL_QUEUE_NONNATIVE: An invalid attempt was made to use a device installation file queue for verification of digital signatures relative to other platforms.")// SPAPI_E_DEVINSTALL_QUEUE_NONNATIVE
        ERR(0x800F0231L, "SPAPI_E_NOT_DISABLEABLE: The device cannot be disabled.")// SPAPI_E_NOT_DISABLEABLE
        ERR(0x800F0232L, "SPAPI_E_CANT_REMOVE_DEVINST: The device could not be dynamically removed.")// SPAPI_E_CANT_REMOVE_DEVINST
        ERR(0x800F1000L, "SPAPI_E_ERROR_NOT_INSTALLED: No installed components were detected.")// SPAPI_E_ERROR_NOT_INSTALLED
        ERR(0x80100001L, "SCARD_F_INTERNAL_ERROR: An internal consistency check failed.")// SCARD_F_INTERNAL_ERROR
        ERR(0x80100002L, "SCARD_E_CANCELLED: The action was cancelled by an SCardCancel request.")// SCARD_E_CANCELLED
        ERR(0x80100003L, "SCARD_E_INVALID_HANDLE: The supplied handle was invalid.")// SCARD_E_INVALID_HANDLE
        ERR(0x80100004L, "SCARD_E_INVALID_PARAMETER: One or more of the supplied parameters could not be properly interpreted.")// SCARD_E_INVALID_PARAMETER
        ERR(0x80100005L, "SCARD_E_INVALID_TARGET: Registry startup information is missing or invalid.")// SCARD_E_INVALID_TARGET
        ERR(0x80100006L, "SCARD_E_NO_MEMORY: Not enough memory available to complete this command.")// SCARD_E_NO_MEMORY
        ERR(0x80100007L, "SCARD_F_WAITED_TOO_LONG: An internal consistency timer has expired.")// SCARD_F_WAITED_TOO_LONG
        ERR(0x80100008L, "SCARD_E_INSUFFICIENT_BUFFER: The data buffer to receive returned data is too small for the returned data.")// SCARD_E_INSUFFICIENT_BUFFER
        ERR(0x80100009L, "SCARD_E_UNKNOWN_READER: The specified reader name is not recognized.")// SCARD_E_UNKNOWN_READER
        ERR(0x8010000AL, "SCARD_E_TIMEOUT: The user-specified timeout value has expired.")// SCARD_E_TIMEOUT
        ERR(0x8010000BL, "SCARD_E_SHARING_VIOLATION: The smart card cannot be accessed because of other connections outstanding.")// SCARD_E_SHARING_VIOLATION
        ERR(0x8010000CL, "SCARD_E_NO_SMARTCARD: The operation requires a Smart Card, but no Smart Card is currently in the device.")// SCARD_E_NO_SMARTCARD
        ERR(0x8010000DL, "SCARD_E_UNKNOWN_CARD: The specified smart card name is not recognized.")// SCARD_E_UNKNOWN_CARD
        ERR(0x8010000EL, "SCARD_E_CANT_DISPOSE: The system could not dispose of the media in the requested manner.")// SCARD_E_CANT_DISPOSE
        ERR(0x8010000FL, "SCARD_E_PROTO_MISMATCH: The requested protocols are incompatible with the protocol currently in use with the smart card.")// SCARD_E_PROTO_MISMATCH
        ERR(0x80100010L, "SCARD_E_NOT_READY: The reader or smart card is not ready to accept commands.")// SCARD_E_NOT_READY
        ERR(0x80100011L, "SCARD_E_INVALID_VALUE: One or more of the supplied parameters values could not be properly interpreted.")// SCARD_E_INVALID_VALUE
        ERR(0x80100012L, "SCARD_E_SYSTEM_CANCELLED: The action was cancelled by the system, presumably to log off or shut down.")// SCARD_E_SYSTEM_CANCELLED
        ERR(0x80100013L, "SCARD_F_COMM_ERROR: An internal communications error has been detected.")// SCARD_F_COMM_ERROR
        ERR(0x80100014L, "SCARD_F_UNKNOWN_ERROR: An internal error has been detected, but the source is unknown.")// SCARD_F_UNKNOWN_ERROR
        ERR(0x80100015L, "SCARD_E_INVALID_ATR: An ATR obtained from the registry is not a valid ATR string.")// SCARD_E_INVALID_ATR
        ERR(0x80100016L, "SCARD_E_NOT_TRANSACTED: An attempt was made to end a non-existent transaction.")// SCARD_E_NOT_TRANSACTED
        ERR(0x80100017L, "SCARD_E_READER_UNAVAILABLE: The specified reader is not currently available for use.")// SCARD_E_READER_UNAVAILABLE
        ERR(0x80100018L, "SCARD_P_SHUTDOWN: The operation has been aborted to allow the server application to exit.")// SCARD_P_SHUTDOWN
        ERR(0x80100019L, "SCARD_E_PCI_TOO_SMALL: The PCI Receive buffer was too small.")// SCARD_E_PCI_TOO_SMALL
        ERR(0x8010001AL, "SCARD_E_READER_UNSUPPORTED: The reader driver does not meet minimal requirements for support.")// SCARD_E_READER_UNSUPPORTED
        ERR(0x8010001BL, "SCARD_E_DUPLICATE_READER: The reader driver did not produce a unique reader name.")// SCARD_E_DUPLICATE_READER
        ERR(0x8010001CL, "SCARD_E_CARD_UNSUPPORTED: The smart card does not meet minimal requirements for support.")// SCARD_E_CARD_UNSUPPORTED
        ERR(0x8010001DL, "SCARD_E_NO_SERVICE: The Smart card resource manager is not running.")// SCARD_E_NO_SERVICE
        ERR(0x8010001EL, "SCARD_E_SERVICE_STOPPED: The Smart card resource manager has shut down.")// SCARD_E_SERVICE_STOPPED
        ERR(0x8010001FL, "SCARD_E_UNEXPECTED: An unexpected card error has occurred.")// SCARD_E_UNEXPECTED
        ERR(0x80100020L, "SCARD_E_ICC_INSTALLATION: No Primary Provider can be found for the smart card.")// SCARD_E_ICC_INSTALLATION
        ERR(0x80100021L, "SCARD_E_ICC_CREATEORDER: The requested order of object creation is not supported.")// SCARD_E_ICC_CREATEORDER
        ERR(0x80100022L, "SCARD_E_UNSUPPORTED_FEATURE: This smart card does not support the requested feature.")// SCARD_E_UNSUPPORTED_FEATURE
        ERR(0x80100023L, "SCARD_E_DIR_NOT_FOUND: The identified directory does not exist in the smart card.")// SCARD_E_DIR_NOT_FOUND
        ERR(0x80100024L, "SCARD_E_FILE_NOT_FOUND: The identified file does not exist in the smart card.")// SCARD_E_FILE_NOT_FOUND
        ERR(0x80100025L, "SCARD_E_NO_DIR: The supplied path does not represent a smart card directory.")// SCARD_E_NO_DIR
        ERR(0x80100026L, "SCARD_E_NO_FILE: The supplied path does not represent a smart card file.")// SCARD_E_NO_FILE
        ERR(0x80100027L, "SCARD_E_NO_ACCESS: Access is denied to this file.")// SCARD_E_NO_ACCESS
        ERR(0x80100028L, "SCARD_E_WRITE_TOO_MANY: An attempt was made to write more data than would fit in the target object.")// SCARD_E_WRITE_TOO_MANY
        ERR(0x80100029L, "SCARD_E_BAD_SEEK: There was an error trying to set the smart card file object pointer.")// SCARD_E_BAD_SEEK
        ERR(0x8010002AL, "SCARD_E_INVALID_CHV: The supplied PIN is incorrect.")// SCARD_E_INVALID_CHV
        ERR(0x8010002BL, "SCARD_E_UNKNOWN_RES_MNG: An unrecognized error code was returned from a layered component.")// SCARD_E_UNKNOWN_RES_MNG
        ERR(0x8010002CL, "SCARD_E_NO_SUCH_CERTIFICATE: The requested certificate does not exist.")// SCARD_E_NO_SUCH_CERTIFICATE
        ERR(0x8010002DL, "SCARD_E_CERTIFICATE_UNAVAILABLE: The requested certificate could not be obtained.")// SCARD_E_CERTIFICATE_UNAVAILABLE
        ERR(0x8010002EL, "SCARD_E_NO_READERS_AVAILABLE: Cannot find a smart card reader.")// SCARD_E_NO_READERS_AVAILABLE
        ERR(0x8010002FL, "SCARD_E_COMM_DATA_LOST: A communications error with the smart card has been detected. Retry the operation.")// SCARD_E_COMM_DATA_LOST
        ERR(0x80100065L, "SCARD_W_UNSUPPORTED_CARD: The reader cannot communicate with the smart card, due to ATR configuration conflicts.")// SCARD_W_UNSUPPORTED_CARD
        ERR(0x80100066L, "SCARD_W_UNRESPONSIVE_CARD: The smart card is not responding to a reset.")// SCARD_W_UNRESPONSIVE_CARD
        ERR(0x80100067L, "SCARD_W_UNPOWERED_CARD: Power has been removed from the smart card, so that further communication is not possible.")// SCARD_W_UNPOWERED_CARD
        ERR(0x80100068L, "SCARD_W_RESET_CARD: The smart card has been reset, so any shared state information is invalid.")// SCARD_W_RESET_CARD
        ERR(0x80100069L, "SCARD_W_REMOVED_CARD: The smart card has been removed, so that further communication is not possible.")// SCARD_W_REMOVED_CARD
        ERR(0x8010006AL, "SCARD_W_SECURITY_VIOLATION: Access was denied because of a security violation.")// SCARD_W_SECURITY_VIOLATION
        ERR(0x8010006BL, "SCARD_W_WRONG_CHV: The card cannot be accessed because the wrong PIN was presented.")// SCARD_W_WRONG_CHV
        ERR(0x8010006CL, "SCARD_W_CHV_BLOCKED: The card cannot be accessed because the maximum number of PIN entry attempts has been reached.")// SCARD_W_CHV_BLOCKED
        ERR(0x8010006DL, "SCARD_W_EOF: The end of the smart card file has been reached.")// SCARD_W_EOF
        ERR(0x8010006EL, "SCARD_W_CANCELLED_BY_USER: The action was cancelled by the user.")// SCARD_W_CANCELLED_BY_USER
        ERR(0x80110401L, "COMADMIN_E_OBJECTERRORS: Errors occurred accessing one or more objects - the ErrorInfo collection may have more detail")// COMADMIN_E_OBJECTERRORS
        ERR(0x80110402L, "COMADMIN_E_OBJECTINVALID: One or more of the object's properties are missing or invalid")// COMADMIN_E_OBJECTINVALID
        ERR(0x80110403L, "COMADMIN_E_KEYMISSING: The object was not found in the catalog")// COMADMIN_E_KEYMISSING
        ERR(0x80110404L, "COMADMIN_E_ALREADYINSTALLED: The object is already registered")// COMADMIN_E_ALREADYINSTALLED
        ERR(0x80110407L, "COMADMIN_E_APP_FILE_WRITEFAIL: Error occurred writing to the application file")// COMADMIN_E_APP_FILE_WRITEFAIL
        ERR(0x80110408L, "COMADMIN_E_APP_FILE_READFAIL: Error occurred reading the application file")// COMADMIN_E_APP_FILE_READFAIL
        ERR(0x80110409L, "COMADMIN_E_APP_FILE_VERSION: Invalid version number in application file")// COMADMIN_E_APP_FILE_VERSION
        ERR(0x8011040AL, "COMADMIN_E_BADPATH: The file path is invalid")// COMADMIN_E_BADPATH
        ERR(0x8011040BL, "COMADMIN_E_APPLICATIONEXISTS: The application is already installed")// COMADMIN_E_APPLICATIONEXISTS
        ERR(0x8011040CL, "COMADMIN_E_ROLEEXISTS: The role already exists")// COMADMIN_E_ROLEEXISTS
        ERR(0x8011040DL, "COMADMIN_E_CANTCOPYFILE: An error occurred copying the file")// COMADMIN_E_CANTCOPYFILE
        ERR(0x8011040FL, "COMADMIN_E_NOUSER: One or more users are not valid")// COMADMIN_E_NOUSER
        ERR(0x80110410L, "COMADMIN_E_INVALIDUSERIDS: One or more users in the application file are not valid")// COMADMIN_E_INVALIDUSERIDS
        ERR(0x80110411L, "COMADMIN_E_NOREGISTRYCLSID: The component's CLSID is missing or corrupt")// COMADMIN_E_NOREGISTRYCLSID
        ERR(0x80110412L, "COMADMIN_E_BADREGISTRYPROGID: The component's progID is missing or corrupt")// COMADMIN_E_BADREGISTRYPROGID
        ERR(0x80110413L, "COMADMIN_E_AUTHENTICATIONLEVEL: Unable to set required authentication level for update request")// COMADMIN_E_AUTHENTICATIONLEVEL
        ERR(0x80110414L, "COMADMIN_E_USERPASSWDNOTVALID: The identity or password set on the application is not valid")// COMADMIN_E_USERPASSWDNOTVALID
        ERR(0x80110418L, "COMADMIN_E_CLSIDORIIDMISMATCH: Application file CLSIDs or IIDs do not match corresponding DLLs")// COMADMIN_E_CLSIDORIIDMISMATCH
        ERR(0x80110419L, "COMADMIN_E_REMOTEINTERFACE: Interface information is either missing or changed")// COMADMIN_E_REMOTEINTERFACE
        ERR(0x8011041AL, "COMADMIN_E_DLLREGISTERSERVER: DllRegisterServer failed on component install")// COMADMIN_E_DLLREGISTERSERVER
        ERR(0x8011041BL, "COMADMIN_E_NOSERVERSHARE: No server file share available")// COMADMIN_E_NOSERVERSHARE
        ERR(0x8011041DL, "COMADMIN_E_DLLLOADFAILED: DLL could not be loaded")// COMADMIN_E_DLLLOADFAILED
        ERR(0x8011041EL, "COMADMIN_E_BADREGISTRYLIBID: The registered TypeLib ID is not valid")// COMADMIN_E_BADREGISTRYLIBID
        ERR(0x8011041FL, "COMADMIN_E_APPDIRNOTFOUND: Application install directory not found")// COMADMIN_E_APPDIRNOTFOUND
        ERR(0x80110423L, "COMADMIN_E_REGISTRARFAILED: Errors occurred while in the component registrar")// COMADMIN_E_REGISTRARFAILED
        ERR(0x80110424L, "COMADMIN_E_COMPFILE_DOESNOTEXIST: The file does not exist")// COMADMIN_E_COMPFILE_DOESNOTEXIST
        ERR(0x80110425L, "COMADMIN_E_COMPFILE_LOADDLLFAIL: The DLL could not be loaded")// COMADMIN_E_COMPFILE_LOADDLLFAIL
        ERR(0x80110426L, "COMADMIN_E_COMPFILE_GETCLASSOBJ: GetClassObject failed in the DLL")// COMADMIN_E_COMPFILE_GETCLASSOBJ
        ERR(0x80110427L, "COMADMIN_E_COMPFILE_CLASSNOTAVAIL: The DLL does not support the components listed in the TypeLib")// COMADMIN_E_COMPFILE_CLASSNOTAVAIL
        ERR(0x80110428L, "COMADMIN_E_COMPFILE_BADTLB: The TypeLib could not be loaded")// COMADMIN_E_COMPFILE_BADTLB
        ERR(0x80110429L, "COMADMIN_E_COMPFILE_NOTINSTALLABLE: The file does not contain components or component information")// COMADMIN_E_COMPFILE_NOTINSTALLABLE
        ERR(0x8011042AL, "COMADMIN_E_NOTCHANGEABLE: Changes to this object and its sub-objects have been disabled")// COMADMIN_E_NOTCHANGEABLE
        ERR(0x8011042BL, "COMADMIN_E_NOTDELETEABLE: The delete function has been disabled for this object")// COMADMIN_E_NOTDELETEABLE
        ERR(0x8011042CL, "COMADMIN_E_SESSION: The server catalog version is not supported")// COMADMIN_E_SESSION
        ERR(0x8011042DL, "COMADMIN_E_COMP_MOVE_LOCKED: The component move was disallowed, because the source or destination application is either a system application or currently locked against changes")// COMADMIN_E_COMP_MOVE_LOCKED
        ERR(0x8011042EL, "COMADMIN_E_COMP_MOVE_BAD_DEST: The component move failed because the destination application no longer exists")// COMADMIN_E_COMP_MOVE_BAD_DEST
        ERR(0x80110430L, "COMADMIN_E_REGISTERTLB: The system was unable to register the TypeLib")// COMADMIN_E_REGISTERTLB
        ERR(0x80110433L, "COMADMIN_E_SYSTEMAPP: This operation can not be performed on the system application")// COMADMIN_E_SYSTEMAPP
        ERR(0x80110434L, "COMADMIN_E_COMPFILE_NOREGISTRAR: The component registrar referenced in this file is not available")// COMADMIN_E_COMPFILE_NOREGISTRAR
        ERR(0x80110435L, "COMADMIN_E_COREQCOMPINSTALLED: A component in the same DLL is already installed")// COMADMIN_E_COREQCOMPINSTALLED
        ERR(0x80110436L, "COMADMIN_E_SERVICENOTINSTALLED: The service is not installed")// COMADMIN_E_SERVICENOTINSTALLED
        ERR(0x80110437L, "COMADMIN_E_PROPERTYSAVEFAILED: One or more property settings are either invalid or in conflict with each other")// COMADMIN_E_PROPERTYSAVEFAILED
        ERR(0x80110438L, "COMADMIN_E_OBJECTEXISTS: The object you are attempting to add or rename already exists")// COMADMIN_E_OBJECTEXISTS
        ERR(0x8011043BL, "COMADMIN_E_REGFILE_CORRUPT: The registration file is corrupt")// COMADMIN_E_REGFILE_CORRUPT
        ERR(0x8011043CL, "COMADMIN_E_PROPERTY_OVERFLOW: The property value is too large")// COMADMIN_E_PROPERTY_OVERFLOW
        ERR(0x8011043EL, "COMADMIN_E_NOTINREGISTRY: Object was not found in registry")// COMADMIN_E_NOTINREGISTRY
        ERR(0x8011043FL, "COMADMIN_E_OBJECTNOTPOOLABLE: This object is not poolable")// COMADMIN_E_OBJECTNOTPOOLABLE
        ERR(0x80110446L, "COMADMIN_E_APPLID_MATCHES_CLSID: A CLSID with the same GUID as the new application ID is already installed on this machine")// COMADMIN_E_APPLID_MATCHES_CLSID
        ERR(0x80110447L, "COMADMIN_E_ROLE_DOES_NOT_EXIST: A role assigned to a component, interface, or method did not exist in the application")// COMADMIN_E_ROLE_DOES_NOT_EXIST
        ERR(0x80110448L, "COMADMIN_E_START_APP_NEEDS_COMPONENTS: You must have components in an application in order to start the application")// COMADMIN_E_START_APP_NEEDS_COMPONENTS
        ERR(0x80110449L, "COMADMIN_E_REQUIRES_DIFFERENT_PLATFORM: This operation is not enabled on this platform")// COMADMIN_E_REQUIRES_DIFFERENT_PLATFORM
        ERR(0x8011044AL, "COMADMIN_E_CAN_NOT_EXPORT_APP_PROXY: Application Proxy is not exportable")// COMADMIN_E_CAN_NOT_EXPORT_APP_PROXY
        ERR(0x8011044BL, "COMADMIN_E_CAN_NOT_START_APP: Failed to start application because it is either a library application or an application proxy")// COMADMIN_E_CAN_NOT_START_APP
        ERR(0x8011044CL, "COMADMIN_E_CAN_NOT_EXPORT_SYS_APP: System application is not exportable")// COMADMIN_E_CAN_NOT_EXPORT_SYS_APP
        ERR(0x8011044DL, "COMADMIN_E_CANT_SUBSCRIBE_TO_COMPONENT: Can not subscribe to this component (the component may have been imported)")// COMADMIN_E_CANT_SUBSCRIBE_TO_COMPONENT
        ERR(0x80110808L, "COMADMIN_E_OBJECT_PARENT_MISSING: One of the objects being inserted or updated does not belong to a valid parent collection")// COMADMIN_E_OBJECT_PARENT_MISSING
        ERR(0x80110809L, "COMADMIN_E_OBJECT_DOES_NOT_EXIST: One of the specified objects cannot be found")// COMADMIN_E_OBJECT_DOES_NOT_EXIST
        ERR(0x8011080AL, "COMADMIN_E_APP_NOT_RUNNING: The specified application is not currently running")// COMADMIN_E_APP_NOT_RUNNING
        ERR(0x8011080DL, "COMADMIN_E_SVCAPP_NOT_POOLABLE_OR_RECYCLABLE: COM+ applications that run as a NT service may not be marked as pooled or recycled")// COMADMIN_E_SVCAPP_NOT_POOLABLE_OR_RECYCLABLE
        ERR(0x8011080EL, "COMADMIN_E_USER_IN_SET: One or more users are already assigned to a local partition set.")// COMADMIN_E_USER_IN_SET
        ERR(0x8011080FL, "COMADMIN_E_CANTRECYCLELIBRARYAPPS: Library applications may not be recycled.")// COMADMIN_E_CANTRECYCLELIBRARYAPPS
        ERR(0x80110811L, "COMADMIN_E_CANTRECYCLESERVICEAPPS: Applications running as NT services may not be recycled.")// COMADMIN_E_CANTRECYCLESERVICEAPPS
        ERR(0x80110812L, "COMADMIN_E_PROCESSALREADYRECYCLED: The process has already been recycled.")// COMADMIN_E_PROCESSALREADYRECYCLED
        ERR(0x80110813L, "COMADMIN_E_PAUSEDPROCESSMAYNOTBERECYCLED: A paused process may not be recycled.")// COMADMIN_E_PAUSEDPROCESSMAYNOTBERECYCLED
        ERR(0x80110814L, "COMADMIN_E_CANTMAKEINPROCSERVICE: Library applications may not be NT services.")// COMADMIN_E_CANTMAKEINPROCSERVICE
        ERR(0x80110815L, "COMADMIN_E_PROGIDINUSEBYCLSID: The ProgID provided to the copy operation is invalid. The ProgID is in use by another registered CLSID.")// COMADMIN_E_PROGIDINUSEBYCLSID
        ERR(0x80110816L, "COMADMIN_E_DEFAULT_PARTITION_NOT_IN_SET: The partition specified as default is not a member of the partition set.")// COMADMIN_E_DEFAULT_PARTITION_NOT_IN_SET
        ERR(0x80110817L, "COMADMIN_E_RECYCLEDPROCESSMAYNOTBEPAUSED: A recycled process may not be paused.")// COMADMIN_E_RECYCLEDPROCESSMAYNOTBEPAUSED
        ERR(0x80110818L, "COMADMIN_E_PARTITION_ACCESSDENIED: Access to the specified partition is denied.")// COMADMIN_E_PARTITION_ACCESSDENIED
        ERR(0x80110600L, "COMQC_E_APPLICATION_NOT_QUEUED: Only COM+ applications marked \"queued\" can be created using the \"queue\" moniker.")// COMQC_E_APPLICATION_NOT_QUEUED
        ERR(0x80110601L, "COMQC_E_NO_QUEUEABLE_INTERFACES: At least one interface must be marked \"queued\" in order to create a queued component instance with the \"queue\" moniker.")// COMQC_E_NO_QUEUEABLE_INTERFACES
        ERR(0x000D0000L, "NS_S_CALLPENDING : The requested operation is pending completion.")// NS_S_CALLPENDING                 
        ERR(0x000D0001L, "NS_S_CALLABORTED : The requested operation was aborted by the client.")// NS_S_CALLABORTED                 
        ERR(0x000D0002L, "NS_S_STREAM_TRUNCATED : The stream was purposefully stopped before completion.")// NS_S_STREAM_TRUNCATED            
        ERR(0x800D0003L, "NS_W_SERVER_BANDWIDTH_LIMIT : The maximum filebitrate value specified is greater than the server's configured maximum bandwidth.")// NS_W_SERVER_BANDWIDTH_LIMIT      
        ERR(0x800D0004L, "NS_W_FILE_BANDWIDTH_LIMIT : The maximum bandwidth value specified is less than the maximum filebitrate.")// NS_W_FILE_BANDWIDTH_LIMIT        
        ERR(0xC00D0005L, "NS_E_NOCONNECTION : There is no connection established with the Windows Media server. The operation failed.")// NS_E_NOCONNECTION                
        ERR(0xC00D0006L, "NS_E_CANNOTCONNECT : Unable to establish a connection to the server.")// NS_E_CANNOTCONNECT               
        ERR(0xC00D0007L, "NS_E_CANNOTDESTROYTITLE : Unable to destroy the title.")// NS_E_CANNOTDESTROYTITLE          
        ERR(0xC00D0008L, "NS_E_CANNOTRENAMETITLE : Unable to rename the title.")// NS_E_CANNOTRENAMETITLE           
        ERR(0xC00D0009L, "NS_E_CANNOTOFFLINEDISK : Unable to offline disk.")// NS_E_CANNOTOFFLINEDISK           
        ERR(0xC00D000AL, "NS_E_CANNOTONLINEDISK : Unable to online disk.")// NS_E_CANNOTONLINEDISK            
        ERR(0xC00D000BL, "NS_E_NOREGISTEREDWALKER : There is no file parser registered for this type of file.")// NS_E_NOREGISTEREDWALKER          
        ERR(0xC00D000CL, "NS_E_NOFUNNEL : There is no data connection established.")// NS_E_NOFUNNEL                    
        ERR(0xC00D000DL, "NS_E_NO_LOCALPLAY : Failed to load the local play DLL.")// NS_E_NO_LOCALPLAY                
        ERR(0xC00D000EL, "NS_E_NETWORK_BUSY : The network is busy.")// NS_E_NETWORK_BUSY                
        ERR(0xC00D000FL, "NS_E_TOO_MANY_SESS : The server session limit was exceeded.")// NS_E_TOO_MANY_SESS               
        ERR(0xC00D0010L, "NS_E_ALREADY_CONNECTED : The network connection already exists.")// NS_E_ALREADY_CONNECTED           
        ERR(0xC00D0011L, "NS_E_INVALID_INDEX : Index %1 is invalid.")// NS_E_INVALID_INDEX               
        ERR(0xC00D0012L, "NS_E_PROTOCOL_MISMATCH : There is no protocol or protocol version supported by both the client and the server.")// NS_E_PROTOCOL_MISMATCH           
        ERR(0xC00D0013L, "NS_E_TIMEOUT : The server, a computer setup to offer multimedia content to other computers, could not handle your request for multimedia content in a timely manner.  Please try again later.")// NS_E_TIMEOUT                     
        ERR(0xC00D0014L, "NS_E_NET_WRITE : Error writing to the network.")// NS_E_NET_WRITE                   
        ERR(0xC00D0015L, "NS_E_NET_READ : Error reading from the network.")// NS_E_NET_READ                    
        ERR(0xC00D0016L, "NS_E_DISK_WRITE : Error writing to a disk.")// NS_E_DISK_WRITE                  
        ERR(0xC00D0017L, "NS_E_DISK_READ : Error reading from a disk.")// NS_E_DISK_READ                   
        ERR(0xC00D0018L, "NS_E_FILE_WRITE : Error writing to a file.")// NS_E_FILE_WRITE                  
        ERR(0xC00D0019L, "NS_E_FILE_READ : Error reading from a file.")// NS_E_FILE_READ                   
        ERR(0xC00D001AL, "NS_E_FILE_NOT_FOUND : The system cannot find the file specified.")// NS_E_FILE_NOT_FOUND              
        ERR(0xC00D001BL, "NS_E_FILE_EXISTS : The file already exists.")// NS_E_FILE_EXISTS                 
        ERR(0xC00D001CL, "NS_E_INVALID_NAME : The file name, directory name, or volume label syntax is incorrect.")// NS_E_INVALID_NAME                
        ERR(0xC00D001DL, "NS_E_FILE_OPEN_FAILED : Failed to open a file.")// NS_E_FILE_OPEN_FAILED            
        ERR(0xC00D001EL, "NS_E_FILE_ALLOCATION_FAILED : Unable to allocate a file.")// NS_E_FILE_ALLOCATION_FAILED      
        ERR(0xC00D001FL, "NS_E_FILE_INIT_FAILED : Unable to initialize a file.")// NS_E_FILE_INIT_FAILED            
        ERR(0xC00D0020L, "NS_E_FILE_PLAY_FAILED : Unable to play a file.")// NS_E_FILE_PLAY_FAILED            
        ERR(0xC00D0021L, "NS_E_SET_DISK_UID_FAILED : Could not set the disk UID.")// NS_E_SET_DISK_UID_FAILED         
        ERR(0xC00D0022L, "NS_E_INDUCED : An error was induced for testing purposes.")// NS_E_INDUCED                     
        ERR(0xC00D0023L, "NS_E_CCLINK_DOWN : Two Content Servers failed to communicate.")// NS_E_CCLINK_DOWN                 
        ERR(0xC00D0024L, "NS_E_INTERNAL : An unknown error occurred.")// NS_E_INTERNAL                    
        ERR(0xC00D0025L, "NS_E_BUSY : The requested resource is in use.")// NS_E_BUSY                        
        ERR(0xC00D0026L, "NS_E_UNRECOGNIZED_STREAM_TYPE : The specified stream type is not recognized.")// NS_E_UNRECOGNIZED_STREAM_TYPE    
        ERR(0xC00D0027L, "NS_E_NETWORK_SERVICE_FAILURE : The network service provider failed.")// NS_E_NETWORK_SERVICE_FAILURE     
        ERR(0xC00D0028L, "NS_E_NETWORK_RESOURCE_FAILURE : An attempt to acquire a network resource failed.")// NS_E_NETWORK_RESOURCE_FAILURE    
        ERR(0xC00D0029L, "NS_E_CONNECTION_FAILURE : The network connection has failed.")// NS_E_CONNECTION_FAILURE          
        ERR(0xC00D002AL, "NS_E_SHUTDOWN : The session is being terminated locally.")// NS_E_SHUTDOWN                    
        ERR(0xC00D002BL, "NS_E_INVALID_REQUEST : The request is invalid in the current state.")// NS_E_INVALID_REQUEST             
        ERR(0xC00D002CL, "NS_E_INSUFFICIENT_BANDWIDTH : There is insufficient bandwidth available to fulfill the request.")// NS_E_INSUFFICIENT_BANDWIDTH      
        ERR(0xC00D002DL, "NS_E_NOT_REBUILDING : The disk is not rebuilding.")// NS_E_NOT_REBUILDING              
        ERR(0xC00D002EL, "NS_E_LATE_OPERATION : An operation requested for a particular time could not be carried out on schedule.")// NS_E_LATE_OPERATION              
        ERR(0xC00D002FL, "NS_E_INVALID_DATA : Invalid or corrupt data was encountered.")// NS_E_INVALID_DATA                
        ERR(0xC00D0030L, "NS_E_FILE_BANDWIDTH_LIMIT : The bandwidth required to stream a file is higher than the maximum file bandwidth allowed on the server.")// NS_E_FILE_BANDWIDTH_LIMIT        
        ERR(0xC00D0031L, "NS_E_OPEN_FILE_LIMIT : The client cannot have any more files open simultaneously.")// NS_E_OPEN_FILE_LIMIT             
        ERR(0xC00D0032L, "NS_E_BAD_CONTROL_DATA : The server received invalid data from the client on the control connection.")// NS_E_BAD_CONTROL_DATA            
        ERR(0xC00D0033L, "NS_E_NO_STREAM : There is no stream available.")// NS_E_NO_STREAM                   
        ERR(0xC00D0034L, "NS_E_STREAM_END : There is no more data in the stream.")// NS_E_STREAM_END                  
        ERR(0xC00D0035L, "NS_E_SERVER_NOT_FOUND : The specified server could not be found.")// NS_E_SERVER_NOT_FOUND            
        ERR(0xC00D0036L, "NS_E_DUPLICATE_NAME : The specified name is already in use.")// NS_E_DUPLICATE_NAME              
        ERR(0xC00D0037L, "NS_E_DUPLICATE_ADDRESS : The specified address is already in use.")// NS_E_DUPLICATE_ADDRESS           
        ERR(0xC00D0038L, "NS_E_BAD_MULTICAST_ADDRESS : The specified address is not a valid multicast address.")// NS_E_BAD_MULTICAST_ADDRESS       
        ERR(0xC00D0039L, "NS_E_BAD_ADAPTER_ADDRESS : The specified adapter address is invalid.")// NS_E_BAD_ADAPTER_ADDRESS         
        ERR(0xC00D003AL, "NS_E_BAD_DELIVERY_MODE : The specified delivery mode is invalid.")// NS_E_BAD_DELIVERY_MODE           
        ERR(0xC00D003BL, "NS_E_INVALID_CHANNEL : The specified station does not exist.")// NS_E_INVALID_CHANNEL             
        ERR(0xC00D003CL, "NS_E_INVALID_STREAM : The specified stream does not exist.")// NS_E_INVALID_STREAM              
        ERR(0xC00D003DL, "NS_E_INVALID_ARCHIVE : The specified archive could not be opened.")// NS_E_INVALID_ARCHIVE             
        ERR(0xC00D003EL, "NS_E_NOTITLES : The system cannot find any titles on the server.")// NS_E_NOTITLES                    
        ERR(0xC00D003FL, "NS_E_INVALID_CLIENT : The system cannot find the client specified.")// NS_E_INVALID_CLIENT              
        ERR(0xC00D0040L, "NS_E_INVALID_BLACKHOLE_ADDRESS : The Blackhole Address is not initialized.")// NS_E_INVALID_BLACKHOLE_ADDRESS   
        ERR(0xC00D0041L, "NS_E_INCOMPATIBLE_FORMAT : The station does not support the stream format.")// NS_E_INCOMPATIBLE_FORMAT         
        ERR(0xC00D0042L, "NS_E_INVALID_KEY : The specified key is not valid.")// NS_E_INVALID_KEY                 
        ERR(0xC00D0043L, "NS_E_INVALID_PORT : The specified port is not valid.")// NS_E_INVALID_PORT                
        ERR(0xC00D0044L, "NS_E_INVALID_TTL : The specified TTL is not valid.")// NS_E_INVALID_TTL                 
        ERR(0xC00D0045L, "NS_E_STRIDE_REFUSED : The request to fast forward or rewind could not be fulfilled.")// NS_E_STRIDE_REFUSED              
        ERR(0xC00D0046L, "NS_E_MMSAUTOSERVER_CANTFINDWALKER : Unable to load the appropriate file parser.")// NS_E_MMSAUTOSERVER_CANTFINDWALKER 
        ERR(0xC00D0047L, "NS_E_MAX_BITRATE : Cannot exceed the maximum bandwidth limit.")// NS_E_MAX_BITRATE                 
        ERR(0xC00D0048L, "NS_E_LOGFILEPERIOD : Invalid value for LogFilePeriod.")// NS_E_LOGFILEPERIOD               
        ERR(0xC00D0049L, "NS_E_MAX_CLIENTS : Cannot exceed the maximum client limit.")// NS_E_MAX_CLIENTS                 
        ERR(0xC00D004AL, "NS_E_LOG_FILE_SIZE : Log File Size too small.")// NS_E_LOG_FILE_SIZE               
        ERR(0xC00D004BL, "NS_E_MAX_FILERATE : Cannot exceed the maximum file rate.")// NS_E_MAX_FILERATE                
        ERR(0xC00D004CL, "NS_E_WALKER_UNKNOWN : Unknown file type.")// NS_E_WALKER_UNKNOWN              
        ERR(0xC00D004DL, "NS_E_WALKER_SERVER : The specified file, %1, cannot be loaded onto the specified server, %2.")// NS_E_WALKER_SERVER               
        ERR(0xC00D004EL, "NS_E_WALKER_USAGE : There was a usage error with file parser.")// NS_E_WALKER_USAGE                
        ERR(0x400D004FL, "NS_I_TIGER_START : The Title Server %1 is running.")// NS_I_TIGER_START                 
        ERR(0xC00D0050L, "NS_E_TIGER_FAIL : The Title Server %1 has failed.")// NS_E_TIGER_FAIL                  
        ERR(0x400D0051L, "NS_I_CUB_START : Content Server %1 (%2) is starting.")// NS_I_CUB_START                   
        ERR(0x400D0052L, "NS_I_CUB_RUNNING : Content Server %1 (%2) is running.")// NS_I_CUB_RUNNING                 
        ERR(0xC00D0053L, "NS_E_CUB_FAIL : Content Server %1 (%2) has failed.")// NS_E_CUB_FAIL                    
        ERR(0x400D0054L, "NS_I_DISK_START : Disk %1 ( %2 ) on Content Server %3, is running.")// NS_I_DISK_START                  
        ERR(0xC00D0055L, "NS_E_DISK_FAIL : Disk %1 ( %2 ) on Content Server %3, has failed.")// NS_E_DISK_FAIL                   
        ERR(0x400D0056L, "NS_I_DISK_REBUILD_STARTED : Started rebuilding disk %1 ( %2 ) on Content Server %3.")// NS_I_DISK_REBUILD_STARTED        
        ERR(0x400D0057L, "NS_I_DISK_REBUILD_FINISHED : Finished rebuilding disk %1 ( %2 ) on Content Server %3.")// NS_I_DISK_REBUILD_FINISHED       
        ERR(0x400D0058L, "NS_I_DISK_REBUILD_ABORTED : Aborted rebuilding disk %1 ( %2 ) on Content Server %3.")// NS_I_DISK_REBUILD_ABORTED        
        ERR(0x400D0059L, "NS_I_LIMIT_FUNNELS : A NetShow administrator at network location %1 set the data stream limit to %2 streams.")// NS_I_LIMIT_FUNNELS               
        ERR(0x400D005AL, "NS_I_START_DISK : A NetShow administrator at network location %1 started disk %2.")// NS_I_START_DISK                  
        ERR(0x400D005BL, "NS_I_STOP_DISK : A NetShow administrator at network location %1 stopped disk %2.")// NS_I_STOP_DISK                   
        ERR(0x400D005CL, "NS_I_STOP_CUB : A NetShow administrator at network location %1 stopped Content Server %2.")// NS_I_STOP_CUB                    
        ERR(0x400D005DL, "NS_I_KILL_VIEWER : A NetShow administrator at network location %1 disconnected viewer %2 from the system.")// NS_I_KILL_VIEWER                 
        ERR(0x400D005EL, "NS_I_REBUILD_DISK : A NetShow administrator at network location %1 started rebuilding disk %2.")// NS_I_REBUILD_DISK                
        ERR(0x800D005FL, "NS_W_UNKNOWN_EVENT : Unknown %1 event encountered.")// NS_W_UNKNOWN_EVENT               
        ERR(0xC00D0060L, "NS_E_MAX_FUNNELS_ALERT : The NetShow data stream limit of %1 streams was reached.")// NS_E_MAX_FUNNELS_ALERT           
        ERR(0xC00D0061L, "NS_E_ALLOCATE_FILE_FAIL : The NetShow Video Server was unable to allocate a %1 block file named %2.")// NS_E_ALLOCATE_FILE_FAIL          
        ERR(0xC00D0062L, "NS_E_PAGING_ERROR : A Content Server was unable to page a block.")// NS_E_PAGING_ERROR                
        ERR(0xC00D0063L, "NS_E_BAD_BLOCK0_VERSION : Disk %1 has unrecognized control block version %2.")// NS_E_BAD_BLOCK0_VERSION          
        ERR(0xC00D0064L, "NS_E_BAD_DISK_UID : Disk %1 has incorrect uid %2.")// NS_E_BAD_DISK_UID                
        ERR(0xC00D0065L, "NS_E_BAD_FSMAJOR_VERSION : Disk %1 has unsupported file system major version %2.")// NS_E_BAD_FSMAJOR_VERSION         
        ERR(0xC00D0066L, "NS_E_BAD_STAMPNUMBER : Disk %1 has bad stamp number in control block.")// NS_E_BAD_STAMPNUMBER             
        ERR(0xC00D0067L, "NS_E_PARTIALLY_REBUILT_DISK : Disk %1 is partially reconstructed.")// NS_E_PARTIALLY_REBUILT_DISK      
        ERR(0xC00D0068L, "NS_E_ENACTPLAN_GIVEUP : EnactPlan gives up.")// NS_E_ENACTPLAN_GIVEUP            
        ERR(0x400D0069L, "MCMADM_I_NO_EVENTS : Event initialization failed, there will be no MCM events.")// MCMADM_I_NO_EVENTS               
        ERR(0xC00D006AL, "MCMADM_E_REGKEY_NOT_FOUND : The key was not found in the registry.")// MCMADM_E_REGKEY_NOT_FOUND        
        ERR(0xC00D006BL, "NS_E_NO_FORMATS : No stream formats were found in an NSC file.")// NS_E_NO_FORMATS                  
        ERR(0xC00D006CL, "NS_E_NO_REFERENCES : No reference URLs were found in an ASX file.")// NS_E_NO_REFERENCES               
        ERR(0xC00D006DL, "NS_E_WAVE_OPEN : Error opening wave device, the device might be in use.")// NS_E_WAVE_OPEN                   
        ERR(0x400D006EL, "NS_I_LOGGING_FAILED : The logging operation failed.")// NS_I_LOGGING_FAILED              
        ERR(0xC00D006FL, "NS_E_CANNOTCONNECTEVENTS : Unable to establish a connection to the NetShow event monitor service.")// NS_E_CANNOTCONNECTEVENTS         
        ERR(0x400D0070L, "NS_I_LIMIT_BANDWIDTH : A NetShow administrator at network location %1 set the maximum bandwidth limit to %2 bps.")// NS_I_LIMIT_BANDWIDTH             
        ERR(0xC00D0071L, "NS_E_NO_DEVICE : No device driver is present on the system.")// NS_E_NO_DEVICE                   
        ERR(0xC00D0072L, "NS_E_NO_SPECIFIED_DEVICE : No specified device driver is present.")// NS_E_NO_SPECIFIED_DEVICE         
        ERR(0xC00D07F1L, "NS_E_NOTHING_TO_DO : NS_E_NOTHING_TO_DO")// NS_E_NOTHING_TO_DO               
        ERR(0xC00D07F2L, "NS_E_NO_MULTICAST : Not receiving data from the server.")// NS_E_NO_MULTICAST                
        ERR(0xC00D00C8L, "NS_E_MONITOR_GIVEUP : Netshow Events Monitor is not operational and has been disconnected.")// NS_E_MONITOR_GIVEUP              
        ERR(0xC00D00C9L, "NS_E_REMIRRORED_DISK : Disk %1 is remirrored.")// NS_E_REMIRRORED_DISK             
        ERR(0xC00D00CAL, "NS_E_INSUFFICIENT_DATA : Insufficient data found.")// NS_E_INSUFFICIENT_DATA           
        ERR(0xC00D00CBL, "NS_E_ASSERT : %1 failed in file %2 line %3.")// NS_E_ASSERT                      
        ERR(0xC00D00CCL, "NS_E_BAD_ADAPTER_NAME : The specified adapter name is invalid.")// NS_E_BAD_ADAPTER_NAME            
        ERR(0xC00D00CDL, "NS_E_NOT_LICENSED : The application is not licensed for this feature.")// NS_E_NOT_LICENSED                
        ERR(0xC00D00CEL, "NS_E_NO_SERVER_CONTACT : Unable to contact the server.")// NS_E_NO_SERVER_CONTACT           
        ERR(0xC00D00CFL, "NS_E_TOO_MANY_TITLES : Maximum number of titles exceeded.")// NS_E_TOO_MANY_TITLES             
        ERR(0xC00D00D0L, "NS_E_TITLE_SIZE_EXCEEDED : Maximum size of a title exceeded.")// NS_E_TITLE_SIZE_EXCEEDED         
        ERR(0xC00D00D1L, "NS_E_UDP_DISABLED : UDP protocol not enabled. Not trying %1!ls!.")// NS_E_UDP_DISABLED                
        ERR(0xC00D00D2L, "NS_E_TCP_DISABLED : TCP protocol not enabled. Not trying %1!ls!.")// NS_E_TCP_DISABLED                
        ERR(0xC00D00D3L, "NS_E_HTTP_DISABLED : HTTP protocol not enabled. Not trying %1!ls!.")// NS_E_HTTP_DISABLED               
        ERR(0xC00D00D4L, "NS_E_LICENSE_EXPIRED : The product license has expired.")// NS_E_LICENSE_EXPIRED             
        ERR(0xC00D00D5L, "NS_E_TITLE_BITRATE : Source file exceeds the per title maximum bitrate. See NetShow Theater documentation for more information.")// NS_E_TITLE_BITRATE               
        ERR(0xC00D00D6L, "NS_E_EMPTY_PROGRAM_NAME : The program name cannot be empty.")// NS_E_EMPTY_PROGRAM_NAME          
        ERR(0xC00D00D7L, "NS_E_MISSING_CHANNEL : Station %1 does not exist.")// NS_E_MISSING_CHANNEL             
        ERR(0xC00D00D8L, "NS_E_NO_CHANNELS : You need to define at least one station before this operation can complete.")// NS_E_NO_CHANNELS                 
        ERR(0xC00D00D9L, "NS_E_INVALID_INDEX2 : The index specified is invalid.")// NS_E_INVALID_INDEX2              
        ERR(0xC00D0190L, "NS_E_CUB_FAIL_LINK : Content Server %1 (%2) has failed its link to Content Server %3.")// NS_E_CUB_FAIL_LINK               
        ERR(0x400D0191L, "NS_I_CUB_UNFAIL_LINK : Content Server %1 (%2) has established its link to Content Server %3.")// NS_I_CUB_UNFAIL_LINK             
        ERR(0xC00D0192L, "NS_E_BAD_CUB_UID : Content Server %1 (%2) has incorrect uid %3.")// NS_E_BAD_CUB_UID                 
        ERR(0x400D0193L, "NS_I_RESTRIPE_START : Restripe operation has started.")// NS_I_RESTRIPE_START              
        ERR(0x400D0194L, "NS_I_RESTRIPE_DONE : Restripe operation has completed.")// NS_I_RESTRIPE_DONE               
        ERR(0xC00D0195L, "NS_E_GLITCH_MODE : Server unreliable because multiple components failed.")// NS_E_GLITCH_MODE                 
        ERR(0x400D0196L, "NS_I_RESTRIPE_DISK_OUT : Content disk %1 (%2) on Content Server %3 has been restriped out.")// NS_I_RESTRIPE_DISK_OUT           
        ERR(0x400D0197L, "NS_I_RESTRIPE_CUB_OUT : Content server %1 (%2) has been restriped out.")// NS_I_RESTRIPE_CUB_OUT            
        ERR(0x400D0198L, "NS_I_DISK_STOP : Disk %1 ( %2 ) on Content Server %3, has been offlined.")// NS_I_DISK_STOP                   
        ERR(0x800D0199L, "NS_I_CATATONIC_FAILURE : Disk %1 ( %2 ) on Content Server %3, will be failed because it is catatonic.")// NS_I_CATATONIC_FAILURE           
        ERR(0x800D019AL, "NS_I_CATATONIC_AUTO_UNFAIL : Disk %1 ( %2 ) on Content Server %3, auto online from catatonic state.")// NS_I_CATATONIC_AUTO_UNFAIL       
        ERR(0xC00D019BL, "NS_E_NO_MEDIA_PROTOCOL : Content Server %1 (%2) is unable to communicate with the Media System Network Protocol.")// NS_E_NO_MEDIA_PROTOCOL           
        ERR(0xC00D0BB8L, "NS_E_INVALID_INPUT_FORMAT : The input media format is invalid.")// NS_E_INVALID_INPUT_FORMAT        
        ERR(0xC00D0BB9L, "NS_E_MSAUDIO_NOT_INSTALLED : The MSAudio codec is not installed on this system.")// NS_E_MSAUDIO_NOT_INSTALLED       
        ERR(0xC00D0BBAL, "NS_E_UNEXPECTED_MSAUDIO_ERROR : An unexpected error occured with the MSAudio codec.")// NS_E_UNEXPECTED_MSAUDIO_ERROR    
        ERR(0xC00D0BBBL, "NS_E_INVALID_OUTPUT_FORMAT : The output media format is invalid.")// NS_E_INVALID_OUTPUT_FORMAT       
        ERR(0xC00D0BBCL, "NS_E_NOT_CONFIGURED : The object must be fully configured before audio samples can be processed.")// NS_E_NOT_CONFIGURED              
        ERR(0xC00D0BBDL, "NS_E_PROTECTED_CONTENT : You need a license to perform the requested operation on this media file.")// NS_E_PROTECTED_CONTENT           
        ERR(0xC00D0BBEL, "NS_E_LICENSE_REQUIRED : You need a license to perform the requested operation on this media file.")// NS_E_LICENSE_REQUIRED            
        ERR(0xC00D0BBFL, "NS_E_TAMPERED_CONTENT : This media file is corrupted or invalid. Contact the content provider for a new file.")// NS_E_TAMPERED_CONTENT            
        ERR(0xC00D0BC0L, "NS_E_LICENSE_OUTOFDATE : The license for this media file has expired. Get a new license or contact the content provider for further assistance.")// NS_E_LICENSE_OUTOFDATE           
        ERR(0xC00D0BC1L, "NS_E_LICENSE_INCORRECT_RIGHTS : You are not allowed to open this file. Contact the content provider for further assistance.")// NS_E_LICENSE_INCORRECT_RIGHTS    
        ERR(0xC00D0BC2L, "NS_E_AUDIO_CODEC_NOT_INSTALLED : The requested audio codec is not installed on this system.")// NS_E_AUDIO_CODEC_NOT_INSTALLED   
        ERR(0xC00D0BC3L, "NS_E_AUDIO_CODEC_ERROR : An unexpected error occurred with the audio codec.")// NS_E_AUDIO_CODEC_ERROR           
        ERR(0xC00D0BC4L, "NS_E_VIDEO_CODEC_NOT_INSTALLED : The requested video codec is not installed on this system.")// NS_E_VIDEO_CODEC_NOT_INSTALLED   
        ERR(0xC00D0BC5L, "NS_E_VIDEO_CODEC_ERROR : An unexpected error occurred with the video codec.")// NS_E_VIDEO_CODEC_ERROR           
        ERR(0xC00D0BC6L, "NS_E_INVALIDPROFILE : The Profile is invalid.")// NS_E_INVALIDPROFILE              
        ERR(0xC00D0BC7L, "NS_E_INCOMPATIBLE_VERSION : A new version of the SDK is needed to play the requested content.")// NS_E_INCOMPATIBLE_VERSION        
        ERR(0x000D0BC8L, "NS_S_REBUFFERING : The requested operation has caused the source to rebuffer.")// NS_S_REBUFFERING                 
        ERR(0x000D0BC9L, "NS_S_DEGRADING_QUALITY : The requested operation has caused the source to degrade codec quality.")// NS_S_DEGRADING_QUALITY           
        ERR(0xC00D0BCAL, "NS_E_OFFLINE_MODE : The requested URL is not available in offline mode.")// NS_E_OFFLINE_MODE                
        ERR(0xC00D0BCBL, "NS_E_NOT_CONNECTED : The requested URL cannot be accessed because there is no network connection.")// NS_E_NOT_CONNECTED               
        ERR(0xC00D0BCCL, "NS_E_TOO_MUCH_DATA : The encoding process was unable to keep up with the amount of supplied data.")// NS_E_TOO_MUCH_DATA               
        ERR(0xC00D0FA0L, "NS_E_NO_CD : There is no compact disc in the drive.")// NS_E_NO_CD                       
        ERR(0xC00D0FA1L, "NS_E_CANT_READ_DIGITAL : Unable to perform digital reads on this compact disc drive.  Please try analog playback via the Tools Options menu.")// NS_E_CANT_READ_DIGITAL           
        ERR(0xC00D0FA2L, "NS_E_DEVICE_DISCONNECTED : The portable device appears to have been disconnected.")// NS_E_DEVICE_DISCONNECTED         
        ERR(0xC00D0FA3L, "NS_E_DEVICE_NOT_SUPPORT_FORMAT : Your Music Player does not support this song's format.")// NS_E_DEVICE_NOT_SUPPORT_FORMAT   
        ERR(0xC00D0FA4L, "NS_E_SLOW_READ_DIGITAL : Digital reads on this compact disc drive are too slow.  Please try analog playback via the Tools Options menu.")// NS_E_SLOW_READ_DIGITAL           
        ERR(0xC00D0FA5L, "NS_E_MIXER_INVALID_LINE : An invalid line error occurred in the mixer.")// NS_E_MIXER_INVALID_LINE          
        ERR(0xC00D0FA6L, "NS_E_MIXER_INVALID_CONTROL : An invalid control error occurred in the mixer.")// NS_E_MIXER_INVALID_CONTROL       
        ERR(0xC00D0FA7L, "NS_E_MIXER_INVALID_VALUE : An invalid value error occurred in the mixer.")// NS_E_MIXER_INVALID_VALUE         
        ERR(0xC00D0FA8L, "NS_E_MIXER_UNKNOWN_MMRESULT : An unrecognized MMRESULT occurred in the mixer.")// NS_E_MIXER_UNKNOWN_MMRESULT      
        ERR(0xC00D0FA9L, "NS_E_USER_STOP : User has stopped the operation.")// NS_E_USER_STOP                   
        ERR(0xC00D0FB4L, "NS_E_WMPXML_NOERROR : A call was made to GetParseError on the XML parser but there was no error to retrieve.")// NS_E_WMPXML_NOERROR              
        ERR(0xC00D0FB5L, "NS_E_WMPXML_ENDOFDATA : The XML Parser ran out of data while parsing.")// NS_E_WMPXML_ENDOFDATA            
        ERR(0xC00D0FB6L, "NS_E_WMPXML_PARSEERROR : A generic parse error occurred in the XML parser but no information is available.")// NS_E_WMPXML_PARSEERROR           
        ERR(0xC00D0FB7L, "NS_E_WMPXML_ATTRIBUTENOTFOUND : A call get GetNamedAttribute or GetNamedAttributeIndex on the XML parser resulted in the index not being found.")// NS_E_WMPXML_ATTRIBUTENOTFOUND    
        ERR(0xC00D0FB8L, "NS_E_WMPXML_PINOTFOUND : A call was made go GetNamedPI on the XML parser, but the requested Processing Instruction was not found.")// NS_E_WMPXML_PINOTFOUND           
        ERR(0xC00D0FB9L, "NS_E_WMPXML_EMPTYDOC : Persist was called on the XML parser, but the parser has no data to persist.")// NS_E_WMPXML_EMPTYDOC             
        ERR(0xC00D0FC8L, "NS_E_WMP_WINDOWSAPIFAILURE : A Windows API call failed but no error information was available.")// NS_E_WMP_WINDOWSAPIFAILURE       
        ERR(0xC00D0FC9L, "NS_E_WMP_RECORDING_NOT_ALLOWED : Copying of this media item is not allowed.")// NS_E_WMP_RECORDING_NOT_ALLOWED   
        ERR(0xC00D0FCAL, "NS_E_DEVICE_NOT_READY : The device is not ready, please check the drive and try again.")// NS_E_DEVICE_NOT_READY            
        ERR(0xC00D0FCBL, "NS_E_DAMAGED_FILE : Windows Media Player cannot play the selected file because it is either damaged or corrupt. Please select a different file.")// NS_E_DAMAGED_FILE                
        ERR(0xC00D0FDEL, "NS_E_WMP_UI_SUBCONTROLSNOTSUPPORTED : The control (%s) does not support creation of sub-controls, yet (%d) sub-controls have been specified.")// NS_E_WMP_UI_SUBCONTROLSNOTSUPPORTED 
        ERR(0xC00D0FDFL, "NS_E_WMP_UI_VERSIONMISMATCH : Version mismatch: (%.1f required, %.1f found).")// NS_E_WMP_UI_VERSIONMISMATCH      
        ERR(0xC00D0FE0L, "NS_E_WMP_UI_NOTATHEMEFILE : The layout manager was given valid XML that wasn't a theme file.")// NS_E_WMP_UI_NOTATHEMEFILE        
        ERR(0xC00D0FE1L, "NS_E_WMP_UI_SUBELEMENTNOTFOUND : The %s subelement could not be found on the %s object.")// NS_E_WMP_UI_SUBELEMENTNOTFOUND   
        ERR(0xC00D0FE2L, "NS_E_WMP_UI_VERSIONPARSE : An error occurred parsing the version tag.\nValid version tags are of the form:\n\n\t<?wmp version='1.0'?>.")// NS_E_WMP_UI_VERSIONPARSE         
        ERR(0xC00D0FE3L, "NS_E_WMP_UI_VIEWIDNOTFOUND : The view specified in for the 'currentViewID' property (%s) was not found in this theme file.")// NS_E_WMP_UI_VIEWIDNOTFOUND       
        ERR(0xC00D0FE4L, "NS_E_WMP_UI_PASSTHROUGH : This error used internally for hit testing.")// NS_E_WMP_UI_PASSTHROUGH          
        ERR(0xC00D0FE5L, "NS_E_WMP_UI_OBJECTNOTFOUND : Attributes were specified for the %s object, but the object was not available to send them to.")// NS_E_WMP_UI_OBJECTNOTFOUND       
        ERR(0xC00D0FE6L, "NS_E_WMP_UI_SECONDHANDLER : The %s event already has a handler, the second handler was ignored.")// NS_E_WMP_UI_SECONDHANDLER        
        ERR(0xC00D0FE7L, "NS_E_WMP_UI_NOSKININZIP : No .wms file found in skin archive.")// NS_E_WMP_UI_NOSKININZIP          
        ERR(0x000D0FE8L, "NS_S_WMP_UI_VERSIONMISMATCH : An upgrade may be needed for the theme manager to correctly show this skin. Skin reports version: %.1f.")// NS_S_WMP_UI_VERSIONMISMATCH      
        ERR(0x000D0FE9L, "NS_S_WMP_EXCEPTION : An error occurred in one of the UI components.")// NS_S_WMP_EXCEPTION               
        ERR(0xC00D1004L, "NS_E_WMP_RBC_JPGMAPPINGIMAGE : JPG Images are not recommended for use as a mappingImage.")// NS_E_WMP_RBC_JPGMAPPINGIMAGE     
        ERR(0xC00D1005L, "NS_E_WMP_JPGTRANSPARENCY : JPG Images are not recommended when using a transparencyColor.")// NS_E_WMP_JPGTRANSPARENCY         
        ERR(0xC00D100EL, "NS_E_WMP_CS_JPGPOSITIONIMAGE : JPG Images are not recommended for use as a positionImage.")// NS_E_WMP_CS_JPGPOSITIONIMAGE     
        ERR(0xC00D100FL, "NS_E_WMP_CS_NOTEVENLYDIVISIBLE : The (%s) image's size is not evenly divisible by the positionImage's size.")// NS_E_WMP_CS_NOTEVENLYDIVISIBLE   
        ERR(0xC00D1018L, "NS_E_WMPZIP_NOTAZIPFILE : The ZIP reader opened a file and its signature didn't match that of ZIP files.")// NS_E_WMPZIP_NOTAZIPFILE          
        ERR(0xC00D1019L, "NS_E_WMPZIP_CORRUPT : The ZIP reader has detected that the file is corrupt.")// NS_E_WMPZIP_CORRUPT              
        ERR(0xC00D101AL, "NS_E_WMPZIP_FILENOTFOUND : GetFileStream, SaveToFile, or SaveTemp file was called on the ZIP reader with a filename that was not found in the zip file.")// NS_E_WMPZIP_FILENOTFOUND         
        ERR(0xC00D1022L, "NS_E_WMP_IMAGE_FILETYPE_UNSUPPORTED : Image type not supported.")// NS_E_WMP_IMAGE_FILETYPE_UNSUPPORTED 
        ERR(0xC00D1023L, "NS_E_WMP_IMAGE_INVALID_FORMAT : Image file may be corrupt.")// NS_E_WMP_IMAGE_INVALID_FORMAT    
        ERR(0xC00D1024L, "NS_E_WMP_GIF_UNEXPECTED_ENDOFFILE : Unexpected end of file. GIF file may be corrupt.")// NS_E_WMP_GIF_UNEXPECTED_ENDOFFILE 
        ERR(0xC00D1025L, "NS_E_WMP_GIF_INVALID_FORMAT : Invalid GIF file.")// NS_E_WMP_GIF_INVALID_FORMAT      
        ERR(0xC00D1026L, "NS_E_WMP_GIF_BAD_VERSION_NUMBER : Invalid GIF version. Only 87a or 89a supported.")// NS_E_WMP_GIF_BAD_VERSION_NUMBER  
        ERR(0xC00D1027L, "NS_E_WMP_GIF_NO_IMAGE_IN_FILE : No images found in GIF file.")// NS_E_WMP_GIF_NO_IMAGE_IN_FILE    
        ERR(0xC00D1028L, "NS_E_WMP_PNG_INVALIDFORMAT : Invalid PNG image file format.")// NS_E_WMP_PNG_INVALIDFORMAT       
        ERR(0xC00D1029L, "NS_E_WMP_PNG_UNSUPPORTED_BITDEPTH : PNG bitdepth not supported.")// NS_E_WMP_PNG_UNSUPPORTED_BITDEPTH 
        ERR(0xC00D102AL, "NS_E_WMP_PNG_UNSUPPORTED_COMPRESSION : Compression format defined in PNG file not supported,")// NS_E_WMP_PNG_UNSUPPORTED_COMPRESSION 
        ERR(0xC00D102BL, "NS_E_WMP_PNG_UNSUPPORTED_FILTER : Filter method defined in PNG file not supported.")// NS_E_WMP_PNG_UNSUPPORTED_FILTER  
        ERR(0xC00D102CL, "NS_E_WMP_PNG_UNSUPPORTED_INTERLACE : Interlace method defined in PNG file not supported.")// NS_E_WMP_PNG_UNSUPPORTED_INTERLACE 
        ERR(0xC00D102DL, "NS_E_WMP_PNG_UNSUPPORTED_BAD_CRC : Bad CRC in PNG file.")// NS_E_WMP_PNG_UNSUPPORTED_BAD_CRC 
        ERR(0xC00D102EL, "NS_E_WMP_BMP_INVALID_BITMASK : Invalid bitmask in BMP file.")// NS_E_WMP_BMP_INVALID_BITMASK     
        ERR(0xC00D102FL, "NS_E_WMP_BMP_TOPDOWN_DIB_UNSUPPORTED : Topdown DIB not supported.")// NS_E_WMP_BMP_TOPDOWN_DIB_UNSUPPORTED 
        ERR(0xC00D1030L, "NS_E_WMP_BMP_BITMAP_NOT_CREATED : Bitmap could not be created.")// NS_E_WMP_BMP_BITMAP_NOT_CREATED  
        ERR(0xC00D1031L, "NS_E_WMP_BMP_COMPRESSION_UNSUPPORTED : Compression format defined in BMP not supported.")// NS_E_WMP_BMP_COMPRESSION_UNSUPPORTED 
        ERR(0xC00D1032L, "NS_E_WMP_BMP_INVALID_FORMAT : Invalid Bitmap format.")// NS_E_WMP_BMP_INVALID_FORMAT      
        ERR(0xC00D1033L, "NS_E_WMP_JPG_JERR_ARITHCODING_NOTIMPL : JPEG Arithmetic coding not supported.")// NS_E_WMP_JPG_JERR_ARITHCODING_NOTIMPL 
        ERR(0xC00D1034L, "NS_E_WMP_JPG_INVALID_FORMAT : Invalid JPEG format.")// NS_E_WMP_JPG_INVALID_FORMAT      
        ERR(0xC00D1035L, "NS_E_WMP_JPG_BAD_DCTSIZE : Invalid JPEG format.")// NS_E_WMP_JPG_BAD_DCTSIZE         
        ERR(0xC00D1036L, "NS_E_WMP_JPG_BAD_VERSION_NUMBER : Internal version error. Unexpected JPEG library version.")// NS_E_WMP_JPG_BAD_VERSION_NUMBER  
        ERR(0xC00D1037L, "NS_E_WMP_JPG_BAD_PRECISION : Internal JPEG Library error. Unsupported JPEG data precision.")// NS_E_WMP_JPG_BAD_PRECISION       
        ERR(0xC00D1038L, "NS_E_WMP_JPG_CCIR601_NOTIMPL : JPEG CCIR601 not supported.")// NS_E_WMP_JPG_CCIR601_NOTIMPL     
        ERR(0xC00D1039L, "NS_E_WMP_JPG_NO_IMAGE_IN_FILE : No image found in JPEG file.")// NS_E_WMP_JPG_NO_IMAGE_IN_FILE    
        ERR(0xC00D103AL, "NS_E_WMP_JPG_READ_ERROR : Could not read JPEG file.")// NS_E_WMP_JPG_READ_ERROR          
        ERR(0xC00D103BL, "NS_E_WMP_JPG_FRACT_SAMPLE_NOTIMPL : JPEG Fractional sampling not supported.")// NS_E_WMP_JPG_FRACT_SAMPLE_NOTIMPL 
        ERR(0xC00D103CL, "NS_E_WMP_JPG_IMAGE_TOO_BIG : JPEG image too large. Maximum image size supported is 65500 X 65500.")// NS_E_WMP_JPG_IMAGE_TOO_BIG       
        ERR(0xC00D103DL, "NS_E_WMP_JPG_UNEXPECTED_ENDOFFILE : Unexpected end of file reached in JPEG file.")// NS_E_WMP_JPG_UNEXPECTED_ENDOFFILE 
        ERR(0xC00D103EL, "NS_E_WMP_JPG_SOF_UNSUPPORTED : Unsupported JPEG SOF marker found.")// NS_E_WMP_JPG_SOF_UNSUPPORTED     
        ERR(0xC00D103FL, "NS_E_WMP_JPG_UNKNOWN_MARKER : Unknown JPEG marker found.")// NS_E_WMP_JPG_UNKNOWN_MARKER      
        ERR(0x000D1040L, "NS_S_WMP_LOADED_GIF_IMAGE : Successfully loaded a GIF file.")// NS_S_WMP_LOADED_GIF_IMAGE        
        ERR(0x000D1041L, "NS_S_WMP_LOADED_PNG_IMAGE : Successfully loaded a PNG file.")// NS_S_WMP_LOADED_PNG_IMAGE        
        ERR(0x000D1042L, "NS_S_WMP_LOADED_BMP_IMAGE : Successfully loaded a BMP file.")// NS_S_WMP_LOADED_BMP_IMAGE        
        ERR(0x000D1043L, "NS_S_WMP_LOADED_JPG_IMAGE : Successfully loaded a JPG file.")// NS_S_WMP_LOADED_JPG_IMAGE        
        ERR(0xC00D1054L, "NS_E_WMG_INVALIDSTATE : Operation attempted in an invalid graph state.")// NS_E_WMG_INVALIDSTATE            
        ERR(0xC00D1055L, "NS_E_WMG_SINKALREADYEXISTS : A renderer cannot be inserted in a stream while one already exists.")// NS_E_WMG_SINKALREADYEXISTS       
        ERR(0xC00D1056L, "NS_E_WMG_NOSDKINTERFACE : A necessary WM SDK interface to complete the operation doesn't exist at this time.")// NS_E_WMG_NOSDKINTERFACE          
        ERR(0xC00D1057L, "NS_E_WMG_NOTALLOUTPUTSRENDERED : Some streams in the current media couldn't be rendered.")// NS_E_WMG_NOTALLOUTPUTSRENDERED   
        ERR(0xC00D1058L, "NS_E_WMR_RENDERFAILED : Failed to render current media.")// NS_E_WMR_RENDERFAILED            
        ERR(0xC00D1059L, "NS_E_WMR_UNSUPPORTEDSTREAM : The stream you are attempting to render is currently not supported.")// NS_E_WMR_UNSUPPORTEDSTREAM       
        ERR(0xC00D105AL, "NS_E_WMR_PINNOTFOUND : An operation was attempted on a pin that doesn't exist in the DirectShow filter graph.")// NS_E_WMR_PINNOTFOUND             
        ERR(0xC00D105BL, "NS_E_WMR_WAITINGONFORMATSWITCH : Specified operation cannot be completed while waiting for a media format change from the SDK.")// NS_E_WMR_WAITINGONFORMATSWITCH   
        ERR(0xC00D1068L, "NS_E_WMX_UNRECOGNIZED_PLAYLIST_FORMAT : The format of this file was not recognized as a valid playlist format.")// NS_E_WMX_UNRECOGNIZED_PLAYLIST_FORMAT 
        ERR(0xC00D1069L, "NS_E_ASX_INVALIDFORMAT : This file was believed to be an ASX playlist, but the format was not recognized.")// NS_E_ASX_INVALIDFORMAT           
        ERR(0xC00D106AL, "NS_E_ASX_INVALIDVERSION : The version of this playlist is not supported.")// NS_E_ASX_INVALIDVERSION          
        ERR(0xC00D106BL, "NS_E_ASX_INVALID_REPEAT_BLOCK : Format of a REPEAT loop within the current playlist file is invalid.")// NS_E_ASX_INVALID_REPEAT_BLOCK    
        ERR(0xC00D106CL, "NS_E_ASX_NOTHING_TO_WRITE : You can not write an empty playlist.")// NS_E_ASX_NOTHING_TO_WRITE        
        ERR(0xC00D106DL, "NS_E_URLLIST_INVALIDFORMAT : This playlist was believed to be a simple list of files, but the format was not recoginized.")// NS_E_URLLIST_INVALIDFORMAT       
        ERR(0xC00D106EL, "NS_E_WMX_ATTRIBUTE_DOES_NOT_EXIST : The specified attribute does not exist.")// NS_E_WMX_ATTRIBUTE_DOES_NOT_EXIST 
        ERR(0xC00D106FL, "NS_E_WMX_ATTRIBUTE_ALREADY_EXISTS : The specified attribute already exists.")// NS_E_WMX_ATTRIBUTE_ALREADY_EXISTS 
        ERR(0xC00D1070L, "NS_E_WMX_ATTRIBUTE_UNRETRIEVABLE : Can not retrieve the specified attribute.")// NS_E_WMX_ATTRIBUTE_UNRETRIEVABLE 
        ERR(0xC00D1071L, "NS_E_WMX_ITEM_DOES_NOT_EXIST : The specified item does not exist in the current playlist.")// NS_E_WMX_ITEM_DOES_NOT_EXIST     
        ERR(0xC00D1072L, "NS_E_WMX_ITEM_TYPE_ILLEGAL : Items of the specified type can not be created within the current playlist.")// NS_E_WMX_ITEM_TYPE_ILLEGAL       
        ERR(0xC00D1073L, "NS_E_WMX_ITEM_UNSETTABLE : The specified item can not be set in the current playlist.")// NS_E_WMX_ITEM_UNSETTABLE         
        ERR(0xC00D107CL, "NS_E_WMPCORE_NOSOURCEURLSTRING : Could not find the source URL for this media.")// NS_E_WMPCORE_NOSOURCEURLSTRING   
        ERR(0xC00D107DL, "NS_E_WMPCORE_COCREATEFAILEDFORGITOBJECT : Failed to create the Global Interface Table.")// NS_E_WMPCORE_COCREATEFAILEDFORGITOBJECT 
        ERR(0xC00D107EL, "NS_E_WMPCORE_FAILEDTOGETMARSHALLEDEVENTHANDLERINTERFACE : Failed to get the marshalled graph event handler interface.")// NS_E_WMPCORE_FAILEDTOGETMARSHALLEDEVENTHANDLERINTERFACE 
        ERR(0xC00D107FL, "NS_E_WMPCORE_BUFFERTOOSMALL : Buffer is too small for copying media type.")// NS_E_WMPCORE_BUFFERTOOSMALL      
        ERR(0xC00D1080L, "NS_E_WMPCORE_UNAVAILABLE : Current state of the player does not allow the operation.")// NS_E_WMPCORE_UNAVAILABLE         
        ERR(0xC00D1081L, "NS_E_WMPCORE_INVALIDPLAYLISTMODE : Playlist manager does not understand the current play mode (shuffle, normal etc).")// NS_E_WMPCORE_INVALIDPLAYLISTMODE 
        ERR(0xC00D1086L, "NS_E_WMPCORE_ITEMNOTINPLAYLIST : Operation failed because the media item is not in the playlist.")// NS_E_WMPCORE_ITEMNOTINPLAYLIST   
        ERR(0xC00D1087L, "NS_E_WMPCORE_PLAYLISTEMPTY : Operation failed because there are no items in the playlist.")// NS_E_WMPCORE_PLAYLISTEMPTY       
        ERR(0xC00D1088L, "NS_E_WMPCORE_NOBROWSER : URL could not be launched since WMP could not find a browser associated with it.")// NS_E_WMPCORE_NOBROWSER           
        ERR(0xC00D1089L, "NS_E_WMPCORE_UNRECOGNIZED_MEDIA_URL : URL unrecognized by WMP runtime.")// NS_E_WMPCORE_UNRECOGNIZED_MEDIA_URL 
        ERR(0xC00D108AL, "NS_E_WMPCORE_GRAPH_NOT_IN_LIST : Graph with the specified URL was not found in the prerolled graph list.")// NS_E_WMPCORE_GRAPH_NOT_IN_LIST   
        ERR(0xC00D108BL, "NS_E_WMPCORE_PLAYLIST_EMPTY_OR_SINGLE_MEDIA : Operation could not be performed because the playlist does not have more than one item.")// NS_E_WMPCORE_PLAYLIST_EMPTY_OR_SINGLE_MEDIA 
        ERR(0xC00D108CL, "NS_E_WMPCORE_ERRORSINKNOTREGISTERED : An error sink was never registered for the calling object.")// NS_E_WMPCORE_ERRORSINKNOTREGISTERED 
        ERR(0xC00D108DL, "NS_E_WMPCORE_ERRORMANAGERNOTAVAILABLE : The error manager is not available to respond to errors.")// NS_E_WMPCORE_ERRORMANAGERNOTAVAILABLE 
        ERR(0xC00D108EL, "NS_E_WMPCORE_WEBHELPFAILED : Failed launching WebHelp URL.")// NS_E_WMPCORE_WEBHELPFAILED       
        ERR(0xC00D108FL, "NS_E_WMPCORE_MEDIA_ERROR_RESUME_FAILED : Could not resume playing next item in playlist.")// NS_E_WMPCORE_MEDIA_ERROR_RESUME_FAILED 
        ERR(0xC00D1090L, "NS_E_WMPCORE_NO_REF_IN_ENTRY : No URL specified in the Ref attribute in playlist file.")// NS_E_WMPCORE_NO_REF_IN_ENTRY     
        ERR(0xC00D1091L, "NS_E_WMPCORE_WMX_LIST_ATTRIBUTE_NAME_EMPTY : An empty string for playlist attribute name was found.")// NS_E_WMPCORE_WMX_LIST_ATTRIBUTE_NAME_EMPTY 
        ERR(0xC00D1092L, "NS_E_WMPCORE_WMX_LIST_ATTRIBUTE_NAME_ILLEGAL : An invalid playlist attribute name was found.")// NS_E_WMPCORE_WMX_LIST_ATTRIBUTE_NAME_ILLEGAL 
        ERR(0xC00D1093L, "NS_E_WMPCORE_WMX_LIST_ATTRIBUTE_VALUE_EMPTY : An empty string for a playlist attribute value was found.")// NS_E_WMPCORE_WMX_LIST_ATTRIBUTE_VALUE_EMPTY 
        ERR(0xC00D1094L, "NS_E_WMPCORE_WMX_LIST_ATTRIBUTE_VALUE_ILLEGAL : An illegal value for a playlist attribute was found.")// NS_E_WMPCORE_WMX_LIST_ATTRIBUTE_VALUE_ILLEGAL 
        ERR(0xC00D1095L, "NS_E_WMPCORE_WMX_LIST_ITEM_ATTRIBUTE_NAME_EMPTY : An empty string for a playlist item attribute name was found.")// NS_E_WMPCORE_WMX_LIST_ITEM_ATTRIBUTE_NAME_EMPTY 
        ERR(0xC00D1096L, "NS_E_WMPCORE_WMX_LIST_ITEM_ATTRIBUTE_NAME_ILLEGAL : An illegal value for a playlist item attribute name was found.")// NS_E_WMPCORE_WMX_LIST_ITEM_ATTRIBUTE_NAME_ILLEGAL 
        ERR(0xC00D1097L, "NS_E_WMPCORE_WMX_LIST_ITEM_ATTRIBUTE_VALUE_EMPTY : An illegal value for a playlist item attribute was found.")// NS_E_WMPCORE_WMX_LIST_ITEM_ATTRIBUTE_VALUE_EMPTY 
        ERR(0xC00D1098L, "NS_E_WMPCORE_LIST_ENTRY_NO_REF : No entries found in the playlist file.")// NS_E_WMPCORE_LIST_ENTRY_NO_REF   
        ERR(0xC00D109AL, "NS_E_WMPCORE_CODEC_NOT_TRUSTED : The codec downloaded for this media does not appear to be properly signed. Installation is not possible.")// NS_E_WMPCORE_CODEC_NOT_TRUSTED   
        ERR(0xC00D109BL, "NS_E_WMPCORE_CODEC_NOT_FOUND : One or more codecs required to play this media could not be found on the codec server.")// NS_E_WMPCORE_CODEC_NOT_FOUND     
        ERR(0xC00D109CL, "NS_E_WMPCORE_CODEC_DOWNLOAD_NOT_ALLOWED : Some of the codecs required by this media are not installed on your system. Since the option for automatic codec acquisition is disabled, no codecs will be downloaded.")// NS_E_WMPCORE_CODEC_DOWNLOAD_NOT_ALLOWED 
        ERR(0xC00D109DL, "NS_E_WMPCORE_ERROR_DOWNLOADING_PLAYLIST : Failed to download the playlist file.")// NS_E_WMPCORE_ERROR_DOWNLOADING_PLAYLIST 
        ERR(0xC00D109EL, "NS_E_WMPCORE_FAILED_TO_BUILD_PLAYLIST : Failed to build the playlist.")// NS_E_WMPCORE_FAILED_TO_BUILD_PLAYLIST 
        ERR(0xC00D109FL, "NS_E_WMPCORE_PLAYLIST_ITEM_ALTERNATE_NONE : Playlist has no alternates to switch into.")// NS_E_WMPCORE_PLAYLIST_ITEM_ALTERNATE_NONE 
        ERR(0xC00D10A0L, "NS_E_WMPCORE_PLAYLIST_ITEM_ALTERNATE_EXHAUSTED : No more playlist alternates available to switch to.")// NS_E_WMPCORE_PLAYLIST_ITEM_ALTERNATE_EXHAUSTED 
        ERR(0xC00D10A1L, "NS_E_WMPCORE_PLAYLIST_ITEM_ALTERNATE_NAME_NOT_FOUND : Could not find the name of the alternate playlist to switch into.")// NS_E_WMPCORE_PLAYLIST_ITEM_ALTERNATE_NAME_NOT_FOUND 
        ERR(0xC00D10A2L, "NS_E_WMPCORE_PLAYLIST_ITEM_ALTERNATE_MORPH_FAILED : Failed to switch to an alternate for this media.")// NS_E_WMPCORE_PLAYLIST_ITEM_ALTERNATE_MORPH_FAILED 
        ERR(0xC00D10A3L, "NS_E_WMPCORE_PLAYLIST_ITEM_ALTERNATE_INIT_FAILED : Failed to initialize an alternate for the media.")// NS_E_WMPCORE_PLAYLIST_ITEM_ALTERNATE_INIT_FAILED 
        ERR(0xC00D10A4L, "NS_E_WMPCORE_MEDIA_ALTERNATE_REF_EMPTY : No URL specified for the roll over Refs in the playlist file.")// NS_E_WMPCORE_MEDIA_ALTERNATE_REF_EMPTY 
        ERR(0xC00D10A5L, "NS_E_WMPCORE_PLAYLIST_NO_EVENT_NAME : Encountered a playlist with no name.")// NS_E_WMPCORE_PLAYLIST_NO_EVENT_NAME 
        ERR(0xC00D10A6L, "NS_E_WMPCORE_PLAYLIST_EVENT_ATTRIBUTE_ABSENT : A required attribute in the event block of the playlist was not found.")// NS_E_WMPCORE_PLAYLIST_EVENT_ATTRIBUTE_ABSENT 
        ERR(0xC00D10A7L, "NS_E_WMPCORE_PLAYLIST_EVENT_EMPTY : No items were found in the event block of the playlist.")// NS_E_WMPCORE_PLAYLIST_EVENT_EMPTY 
        ERR(0xC00D10A8L, "NS_E_WMPCORE_PLAYLIST_STACK_EMPTY : No playlist was found while returning from a nested playlist.")// NS_E_WMPCORE_PLAYLIST_STACK_EMPTY 
        ERR(0xC00D10A9L, "NS_E_WMPCORE_CURRENT_MEDIA_NOT_ACTIVE : The media item is not active currently.")// NS_E_WMPCORE_CURRENT_MEDIA_NOT_ACTIVE 
        ERR(0xC00D10ABL, "NS_E_WMPCORE_USER_CANCEL : Open was aborted by user.")// NS_E_WMPCORE_USER_CANCEL         
        ERR(0xC00D10ACL, "NS_E_WMPCORE_PLAYLIST_REPEAT_EMPTY : No items were found inside the playlist repeat block.")// NS_E_WMPCORE_PLAYLIST_REPEAT_EMPTY 
        ERR(0xC00D10ADL, "NS_E_WMPCORE_PLAYLIST_REPEAT_START_MEDIA_NONE : Media object corresponding to start of a playlist repeat block was not found.")// NS_E_WMPCORE_PLAYLIST_REPEAT_START_MEDIA_NONE 
        ERR(0xC00D10AEL, "NS_E_WMPCORE_PLAYLIST_REPEAT_END_MEDIA_NONE : Media object corresponding to the end of a playlist repeat block was not found.")// NS_E_WMPCORE_PLAYLIST_REPEAT_END_MEDIA_NONE 
        ERR(0xC00D10AFL, "NS_E_WMPCORE_INVALID_PLAYLIST_URL : Playlist URL supplied to the playlist manager is invalid.")// NS_E_WMPCORE_INVALID_PLAYLIST_URL 
        ERR(0xC00D10B0L, "NS_E_WMPCORE_MISMATCHED_RUNTIME : Player is selecting a runtime that is not valid for this media file type.")// NS_E_WMPCORE_MISMATCHED_RUNTIME  
        ERR(0xC00D10B1L, "NS_E_WMPCORE_PLAYLIST_IMPORT_FAILED_NO_ITEMS : The import has failed because none of the items in the playlist could be imported.")// NS_E_WMPCORE_PLAYLIST_IMPORT_FAILED_NO_ITEMS 
        ERR(0xC00D10B2L, "NS_E_WMPCORE_VIDEO_TRANSFORM_FILTER_INSERTION : An error has occurred that could prevent the changing of the video contrast on this media.")// NS_E_WMPCORE_VIDEO_TRANSFORM_FILTER_INSERTION 
        ERR(0xC00D10B3L, "NS_E_WMPCORE_MEDIA_UNAVAILABLE : Unable to acess this media, you may not be connected to the network.")// NS_E_WMPCORE_MEDIA_UNAVAILABLE   
        ERR(0xC00D10B4L, "NS_E_WMPCORE_WMX_ENTRYREF_NO_REF : The playlist contains an ENTRYREF for which no href was parsed. Check the syntax of playlist file.")// NS_E_WMPCORE_WMX_ENTRYREF_NO_REF 
        ERR(0xC00D10B5L, "NS_E_WMPCORE_NO_PLAYABLE_MEDIA_IN_PLAYLIST : Could not play any media in the playlist.")// NS_E_WMPCORE_NO_PLAYABLE_MEDIA_IN_PLAYLIST 
        ERR(0xC00D10B6L, "NS_E_WMPCORE_PLAYLIST_EMPTY_NESTED_PLAYLIST_SKIPPED_ITEMS : Failed to open the nested playlist because it has no items after player has ignored entries which are pointing to other playlists.")// NS_E_WMPCORE_PLAYLIST_EMPTY_NESTED_PLAYLIST_SKIPPED_ITEMS 
        ERR(0xC00D10B7L, "NS_E_WMPCORE_BUSY : The player could not handle your request for multimedia content in a timely manner. Please try again later.")// NS_E_WMPCORE_BUSY                
        ERR(0x000D10FEL, "NS_S_WMPCORE_PLAYLISTCLEARABORT : Failed to clear playlist because it was aborted by user.")// NS_S_WMPCORE_PLAYLISTCLEARABORT  
        ERR(0x000D10FFL, "NS_S_WMPCORE_PLAYLISTREMOVEITEMABORT : Failed to remove item in the playlist since it was aborted by user.")// NS_S_WMPCORE_PLAYLISTREMOVEITEMABORT 
        ERR(0x000D1102L, "NS_S_WMPCORE_PLAYLIST_CREATION_PENDING : Playlist is being generated asynchronously.")// NS_S_WMPCORE_PLAYLIST_CREATION_PENDING 
        ERR(0x000D1103L, "NS_S_WMPCORE_MEDIA_VALIDATION_PENDING : Validation of the media is pending...")// NS_S_WMPCORE_MEDIA_VALIDATION_PENDING 
        ERR(0x000D1104L, "NS_S_WMPCORE_PLAYLIST_REPEAT_SECONDARY_SEGMENTS_IGNORED : Encountered more than one Repeat block during ASX processing.")// NS_S_WMPCORE_PLAYLIST_REPEAT_SECONDARY_SEGMENTS_IGNORED 
        ERR(0x000D1105L, "NS_S_WMPCORE_COMMAND_NOT_AVAILABLE : Current state of WMP disallows calling this method or property.")// NS_S_WMPCORE_COMMAND_NOT_AVAILABLE 
        ERR(0x000D1106L, "NS_S_WMPCORE_PLAYLIST_NAME_AUTO_GENERATED : Name for the playlist has been auto generated.")// NS_S_WMPCORE_PLAYLIST_NAME_AUTO_GENERATED 
        ERR(0x000D1107L, "NS_S_WMPCORE_PLAYLIST_IMPORT_MISSING_ITEMS : The imported playlist does not contain all items from the original.")// NS_S_WMPCORE_PLAYLIST_IMPORT_MISSING_ITEMS 
        ERR(0x000D1108L, "NS_S_WMPCORE_PLAYLIST_COLLAPSED_TO_SINGLE_MEDIA : The playlist has been collapsed into a single media.")// NS_S_WMPCORE_PLAYLIST_COLLAPSED_TO_SINGLE_MEDIA 
        ERR(0xC00D1126L, "NS_E_WMPIM_USEROFFLINE : System is not connected to the Internet.")// NS_E_WMPIM_USEROFFLINE           
        ERR(0xC00D1127L, "NS_E_WMPIM_USERCANCELED : User cancelled attempt to connect to the Internet.")// NS_E_WMPIM_USERCANCELED          
        ERR(0xC00D1128L, "NS_E_WMPIM_DIALUPFAILED : Attempt to dial connection to the Internet failed.")// NS_E_WMPIM_DIALUPFAILED          
        ERR(0xC00D1130L, "NS_E_WMPBR_NOLISTENER : No window is currently listening to Backup and Restore events.")// NS_E_WMPBR_NOLISTENER            
        ERR(0xC00D1131L, "NS_E_WMPBR_BACKUPCANCEL : Backup of your licenses has been cancelled.  Please try again to ensure license backup.")// NS_E_WMPBR_BACKUPCANCEL          
        ERR(0xC00D1132L, "NS_E_WMPBR_RESTORECANCEL : Restoration of your licenses has been cancelled.  Please try again to ensure license restoration.")// NS_E_WMPBR_RESTORECANCEL         
        ERR(0xC00D1133L, "NS_E_WMPBR_ERRORWITHURL : An error occured during the backup or restore operation that requires a web page be displayed to the user.")// NS_E_WMPBR_ERRORWITHURL          
        ERR(0xC00D1134L, "NS_E_WMPBR_NAMECOLLISION : Backup of your licenses was not successfully completed.  Please try again or click Details for additional assistance.")// NS_E_WMPBR_NAMECOLLISION         
        ERR(0x000D1135L, "NS_S_WMPBR_SUCCESS : Backup or Restore successful!.")// NS_S_WMPBR_SUCCESS               
        ERR(0x000D1136L, "NS_S_WMPBR_PARTIALSUCCESS : Transfer complete with limitations.")// NS_S_WMPBR_PARTIALSUCCESS        
        ERR(0x000D1144L, "NS_S_WMPEFFECT_TRANSPARENT : Request to the effects control to change transparency status to transparent.")// NS_S_WMPEFFECT_TRANSPARENT       
        ERR(0x000D1145L, "NS_S_WMPEFFECT_OPAQUE : Request to the effects control to change transparency status to opaque.")// NS_S_WMPEFFECT_OPAQUE            
        ERR(0x000D114EL, "NS_S_OPERATION_PENDING : The requested application pane is performing an operation and will not be relased.")// NS_S_OPERATION_PENDING           
        ERR(0xC00D1388L, "NS_E_REDIRECT : The client is redirected to another server.")// NS_E_REDIRECT                    
        ERR(0xC00D1389L, "NS_E_STALE_PRESENTATION : The streaming media description is no longer current.")// NS_E_STALE_PRESENTATION          
        ERR(0xC00D138AL, "NS_E_NAMESPACE_WRONG_PERSIST : Attempt to create a persistent namespace node under a transient parent node.")// NS_E_NAMESPACE_WRONG_PERSIST     
        ERR(0xC00D138BL, "NS_E_NAMESPACE_WRONG_TYPE : Unable to store a value in a namespace node of different value type.")// NS_E_NAMESPACE_WRONG_TYPE        
        ERR(0xC00D138CL, "NS_E_NAMESPACE_NODE_CONFLICT : Unable to remove the root namespace node.")// NS_E_NAMESPACE_NODE_CONFLICT     
        ERR(0xC00D138DL, "NS_E_NAMESPACE_NODE_NOT_FOUND : Could not find the specified namespace node.")// NS_E_NAMESPACE_NODE_NOT_FOUND    
        ERR(0xC00D138EL, "NS_E_NAMESPACE_BUFFER_TOO_SMALL : The buffer supplied to hold namespace node string is too small.")// NS_E_NAMESPACE_BUFFER_TOO_SMALL  
        ERR(0xC00D138FL, "NS_E_NAMESPACE_TOO_MANY_CALLBACKS : Callback list on a namespace node is at maximum size.")// NS_E_NAMESPACE_TOO_MANY_CALLBACKS 
        ERR(0xC00D1390L, "NS_E_NAMESPACE_DUPLICATE_CALLBACK : Attempt to register an already-registered callback on a namespace node.")// NS_E_NAMESPACE_DUPLICATE_CALLBACK 
        ERR(0xC00D1391L, "NS_E_NAMESPACE_CALLBACK_NOT_FOUND : Could not find callback in namespace when attempting to remove callback.")// NS_E_NAMESPACE_CALLBACK_NOT_FOUND 
        ERR(0xC00D1392L, "NS_E_NAMESPACE_NAME_TOO_LONG : The length of a namespace node name exceeds the allowed maximum length.")// NS_E_NAMESPACE_NAME_TOO_LONG     
        ERR(0xC00D1393L, "NS_E_NAMESPACE_DUPLICATE_NAME : Cannot create a namespace node which already exists.")// NS_E_NAMESPACE_DUPLICATE_NAME    
        ERR(0xC00D1394L, "NS_E_NAMESPACE_EMPTY_NAME : The name of a namespace node cannot be a null string.")// NS_E_NAMESPACE_EMPTY_NAME        
        ERR(0xC00D1395L, "NS_E_NAMESPACE_INDEX_TOO_LARGE : Finding a child namespace node by index failed because the index exceeded the number of children.")// NS_E_NAMESPACE_INDEX_TOO_LARGE   
        ERR(0xC00D1396L, "NS_E_NAMESPACE_BAD_NAME : The name supplied for a namespace node is not valid.")// NS_E_NAMESPACE_BAD_NAME          
        ERR(0xC00D1397L, "NS_E_CACHE_ARCHIVE_CONFLICT : Archive request conflicts with other requests in progress.")// NS_E_CACHE_ARCHIVE_CONFLICT      
        ERR(0xC00D1398L, "NS_E_CACHE_ORIGIN_SERVER_NOT_FOUND : The specified origin server cannot be found.")// NS_E_CACHE_ORIGIN_SERVER_NOT_FOUND 
        ERR(0xC00D1399L, "NS_E_CACHE_ORIGIN_SERVER_TIMEOUT : The specified origin server does not respond.")// NS_E_CACHE_ORIGIN_SERVER_TIMEOUT 
        ERR(0xC00D139AL, "NS_E_CACHE_NOT_BROADCAST : The internal code for HTTP status code 412 Precondition Failed due to not broadcast type.")// NS_E_CACHE_NOT_BROADCAST         
        ERR(0xC00D139BL, "NS_E_CACHE_CANNOT_BE_CACHED : The internal code for HTTP status code 403 Forbidden due to not cacheable.")// NS_E_CACHE_CANNOT_BE_CACHED      
        ERR(0xC00D139CL, "NS_E_CACHE_NOT_MODIFIED : The internal code for HTTP status code 304 Not Modified.")// NS_E_CACHE_NOT_MODIFIED          
        ERR(0xC00D139DL, "NS_E_CANNOT_REMOVE_PUBPOINT : The Publishing Point can not be removed.")// NS_E_CANNOT_REMOVE_PUBPOINT      
        ERR(0xC00D1B58L, "NS_E_BAD_MARKIN : The Mark In time should be greater than 0 and less than Mark Out time.")// NS_E_BAD_MARKIN                  
        ERR(0xC00D1B59L, "NS_E_BAD_MARKOUT : The Mark Out time should be greater than Mark In time and less than file duration.")// NS_E_BAD_MARKOUT                 
        ERR(0xC00D1B5AL, "NS_E_NOMATCHING_MEDIASOURCE : No matching media source is found in source group %1.")// NS_E_NOMATCHING_MEDIASOURCE      
        ERR(0xC00D1B5BL, "NS_E_UNSUPPORTED_SOURCETYPE : Unsupported source type.")// NS_E_UNSUPPORTED_SOURCETYPE      
        ERR(0xC00D1B5CL, "NS_E_TOO_MANY_AUDIO : No more than 1 audio input is allowed.")// NS_E_TOO_MANY_AUDIO              
        ERR(0xC00D1B5DL, "NS_E_TOO_MANY_VIDEO : No more than 2 video inputs are allowed.")// NS_E_TOO_MANY_VIDEO              
        ERR(0xC00D1B5EL, "NS_E_NOMATCHING_ELEMENT : No matching element is found in the list.")// NS_E_NOMATCHING_ELEMENT          
        ERR(0xC00D1B5FL, "NS_E_MISMATCHED_MEDIACONTENT : The profile's media content doesn't match the media content defined in the source group.")// NS_E_MISMATCHED_MEDIACONTENT     
        ERR(0xC00D1B60L, "NS_E_CANNOT_DELETE_ACTIVE_SOURCEGROUP : Cannot remove an active source group from the source group collection while encoder is currently running.")// NS_E_CANNOT_DELETE_ACTIVE_SOURCEGROUP 
        ERR(0xC00D1B61L, "NS_E_AUDIODEVICE_BUSY : Cannot open specified audio capture device because it is in use right now.")// NS_E_AUDIODEVICE_BUSY            
        ERR(0xC00D1B62L, "NS_E_AUDIODEVICE_UNEXPECTED : Cannot open specified audio capture device because unexpected error occurred.")// NS_E_AUDIODEVICE_UNEXPECTED      
        ERR(0xC00D1B63L, "NS_E_AUDIODEVICE_BADFORMAT : Audio capture device doesn't support specified audio format.")// NS_E_AUDIODEVICE_BADFORMAT       
        ERR(0xC00D1B64L, "NS_E_VIDEODEVICE_BUSY : Cannot open specified video capture device because it is in use right now.")// NS_E_VIDEODEVICE_BUSY            
        ERR(0xC00D1B65L, "NS_E_VIDEODEVICE_UNEXPECTED : Cannot open specified video capture device because unexpected error occurred.")// NS_E_VIDEODEVICE_UNEXPECTED      
        ERR(0xC00D1B66L, "NS_E_INVALIDCALL_WHILE_ENCODER_RUNNING : This operation is not allowed while encoder is running.")// NS_E_INVALIDCALL_WHILE_ENCODER_RUNNING 
        ERR(0xC00D1B67L, "NS_E_NO_PROFILE_IN_SOURCEGROUP : No profile is set in source group.")// NS_E_NO_PROFILE_IN_SOURCEGROUP   
        ERR(0xC00D1B68L, "NS_E_VIDEODRIVER_UNSTABLE : The video capture driver returned an unrecoverable error.  It is now in an unstable state.")// NS_E_VIDEODRIVER_UNSTABLE        
        ERR(0xC00D1B69L, "NS_E_VIDCAPSTARTFAILED : The video input device could not be started.")// NS_E_VIDCAPSTARTFAILED           
        ERR(0xC00D1B6AL, "NS_E_VIDSOURCECOMPRESSION : The video input source does not support the requested output format or color depth.")// NS_E_VIDSOURCECOMPRESSION        
        ERR(0xC00D1B6BL, "NS_E_VIDSOURCESIZE : The video input source does not support the request capture size.")// NS_E_VIDSOURCESIZE               
        ERR(0xC00D1B6CL, "NS_E_ICMQUERYFORMAT : Unable to obtain output information from video compressor.")// NS_E_ICMQUERYFORMAT              
        ERR(0xC00D1B6DL, "NS_E_VIDCAPCREATEWINDOW : Unable to create video capture window.")// NS_E_VIDCAPCREATEWINDOW          
        ERR(0xC00D1B6EL, "NS_E_VIDCAPDRVINUSE : There already is a running stream active on this video input device.")// NS_E_VIDCAPDRVINUSE              
        ERR(0xC00D1B6FL, "NS_E_NO_MEDIAFORMAT_IN_SOURCE : No media format is set in source.")// NS_E_NO_MEDIAFORMAT_IN_SOURCE    
        ERR(0xC00D1B70L, "NS_E_NO_VALID_OUTPUT_STREAM : Cannot find valid output stream from source.")// NS_E_NO_VALID_OUTPUT_STREAM      
        ERR(0xC00D1B71L, "NS_E_NO_VALID_SOURCE_PLUGIN : Cannot find valid source plugin to support specified source.")// NS_E_NO_VALID_SOURCE_PLUGIN      
        ERR(0xC00D1B72L, "NS_E_NO_ACTIVE_SOURCEGROUP : No source group is currently active.")// NS_E_NO_ACTIVE_SOURCEGROUP       
        ERR(0xC00D1B73L, "NS_E_NO_SCRIPT_STREAM : No script stream is set in current active source group.")// NS_E_NO_SCRIPT_STREAM            
        ERR(0xC00D1B74L, "NS_E_INVALIDCALL_WHILE_ARCHIVAL_RUNNING : This operation is not allowed when file archival is started.")// NS_E_INVALIDCALL_WHILE_ARCHIVAL_RUNNING 
        ERR(0xC00D1B75L, "NS_E_INVALIDPACKETSIZE : The MaxPacketSize value specified is invalid.")// NS_E_INVALIDPACKETSIZE           
        ERR(0xC00D1B76L, "NS_E_PLUGIN_CLSID_NOTINVALID : The plugin CLSID specified is invalid.")// NS_E_PLUGIN_CLSID_NOTINVALID     
        ERR(0xC00D1B77L, "NS_E_UNSUPPORTED_ARCHIVETYPE : This Archive type is not supported.")// NS_E_UNSUPPORTED_ARCHIVETYPE     
        ERR(0xC00D1B78L, "NS_E_UNSUPPORTED_ARCHIVEOPERATION : This Archive operation is not supported.")// NS_E_UNSUPPORTED_ARCHIVEOPERATION 
        ERR(0xC00D1B79L, "NS_E_ARCHIVE_FILENAME_NOTSET : The local archive filename was not set.")// NS_E_ARCHIVE_FILENAME_NOTSET     
        ERR(0xC00D1B7AL, "NS_E_SOURCEGROUP_NOTPREPARED : The SourceGroup is not yet prepared.")// NS_E_SOURCEGROUP_NOTPREPARED     
        ERR(0xC00D1B7BL, "NS_E_PROFILE_MISMATCH : Profiles on the sourcegroups do not match.")// NS_E_PROFILE_MISMATCH            
        ERR(0xC00D1B7CL, "NS_E_INCORRECTCLIPSETTINGS : The clip settings specified on the source are incorrect.")// NS_E_INCORRECTCLIPSETTINGS       
        ERR(0xC00D1B7DL, "NS_E_NOSTATSAVAILABLE : No statistics are available at this time.")// NS_E_NOSTATSAVAILABLE            
        ERR(0xC00D1B7EL, "NS_E_NOTARCHIVING : Encoder is not archiving.")// NS_E_NOTARCHIVING                
        ERR(0xC00D1B7FL, "NS_E_INVALIDCALL_WHILE_ENCODER_STOPPED : This operation is not allowed while encoder is not running.")// NS_E_INVALIDCALL_WHILE_ENCODER_STOPPED 
        ERR(0xC00D1B80L, "NS_E_NOSOURCEGROUPS : This SourceGroupCollection doesnt contain any SourceGroups.")// NS_E_NOSOURCEGROUPS              
        ERR(0xC00D1B81L, "NS_E_INVALIDINPUTFPS : Because this source group does not have a frame rate of 30 frames per second, you cannot use the inverse telecine feature.")// NS_E_INVALIDINPUTFPS             
        ERR(0xC00D1B82L, "NS_E_NO_DATAVIEW_SUPPORT : Internal problems are preventing the preview or postview of your content.")// NS_E_NO_DATAVIEW_SUPPORT         
        ERR(0xC00D1B83L, "NS_E_CODEC_UNAVAILABLE : One or more codecs required to open this media could not be found.")// NS_E_CODEC_UNAVAILABLE           
        ERR(0xC00D1B84L, "NS_E_ARCHIVE_SAME_AS_INPUT : The output archive file specified is the same as an input source in one of the source groups.")// NS_E_ARCHIVE_SAME_AS_INPUT       
        ERR(0xC00D1B85L, "NS_E_SOURCE_NOTSPECIFIED : The input source has not been setup completely.")// NS_E_SOURCE_NOTSPECIFIED         
        ERR(0xC00D1B86L, "NS_E_NO_REALTIME_TIMECOMPRESSION : Cannot apply time compression transform plug-in to a real time broadcast session.")// NS_E_NO_REALTIME_TIMECOMPRESSION 
        ERR(0xC00D1B87L, "NS_E_UNSUPPORTED_ENCODER_DEVICE : The Encoder was unable to open this device. Please see the system requirements for more information.")// NS_E_UNSUPPORTED_ENCODER_DEVICE  
        ERR(0xC00D1B88L, "NS_E_UNEXPECTED_DISPLAY_SETTINGS : Encoding cannot start because the display size or color setting has changed since the current session was defined. Restore the previous settings or create a new session.")// NS_E_UNEXPECTED_DISPLAY_SETTINGS 
        ERR(0xC00D1B89L, "NS_E_NO_AUDIODATA : No audio data has been received for multiple seconds.  Check the audio source and restart the encoder.")// NS_E_NO_AUDIODATA                
        ERR(0xC00D1B8AL, "NS_E_INPUTSOURCE_PROBLEM : One or all of your specified input sources are not working properly. Make sure your input sources are configured correctly.")// NS_E_INPUTSOURCE_PROBLEM         
        ERR(0xC00D1B8BL, "NS_E_WME_VERSION_MISMATCH : The supplied configuration file is not supported by this version of the encoder.")// NS_E_WME_VERSION_MISMATCH        
        ERR(0xC00D2711L, "NS_E_DRM_INVALID_APPLICATION : A problem has occurred in the Digital Rights Management component. Contact product support for this application.")// NS_E_DRM_INVALID_APPLICATION     
        ERR(0xC00D2712L, "NS_E_DRM_LICENSE_STORE_ERROR : License storage is not working. Contact Microsoft product support.")// NS_E_DRM_LICENSE_STORE_ERROR     
        ERR(0xC00D2713L, "NS_E_DRM_SECURE_STORE_ERROR : Secure storage is not working. Contact Microsoft product support.")// NS_E_DRM_SECURE_STORE_ERROR      
        ERR(0xC00D2714L, "NS_E_DRM_LICENSE_STORE_SAVE_ERROR : License acquisition did not work. Acquire a new license or contact the content provider for further assistance.")// NS_E_DRM_LICENSE_STORE_SAVE_ERROR 
        ERR(0xC00D2715L, "NS_E_DRM_SECURE_STORE_UNLOCK_ERROR : A problem has occurred in the Digital Rights Management component. Contact Microsoft product support.")// NS_E_DRM_SECURE_STORE_UNLOCK_ERROR 
        ERR(0xC00D2716L, "NS_E_DRM_INVALID_CONTENT : The media file is corrupted. Contact the content provider to get a new file.")// NS_E_DRM_INVALID_CONTENT         
        ERR(0xC00D2717L, "NS_E_DRM_UNABLE_TO_OPEN_LICENSE : The license is corrupted. Acquire a new license.")// NS_E_DRM_UNABLE_TO_OPEN_LICENSE  
        ERR(0xC00D2718L, "NS_E_DRM_INVALID_LICENSE : The license is corrupted or invalid. Acquire a new license")// NS_E_DRM_INVALID_LICENSE         
        ERR(0xC00D2719L, "NS_E_DRM_INVALID_MACHINE : Licenses cannot be copied from one computer to another. Use License Management to transfer licenses, or get a new license for the media file.")// NS_E_DRM_INVALID_MACHINE         
        ERR(0xC00D271AL, "NS_E_DRM_LICENSE_EVAL_FAILED : The license is corrupted or invalid. Acquire a new license or reinstall the application.")// NS_E_DRM_LICENSE_EVAL_FAILED     
        ERR(0xC00D271BL, "NS_E_DRM_ENUM_LICENSE_FAILED : License storage is not working. Contact Microsoft product support.")// NS_E_DRM_ENUM_LICENSE_FAILED     
        ERR(0xC00D271CL, "NS_E_DRM_INVALID_LICENSE_REQUEST : The media file is corrupted. Contact the content provider to get a new file.")// NS_E_DRM_INVALID_LICENSE_REQUEST 
        ERR(0xC00D271DL, "NS_E_DRM_UNABLE_TO_INITIALIZE : A problem has occurred in the Digital Rights Management component. Contact Microsoft product support.")// NS_E_DRM_UNABLE_TO_INITIALIZE    
        ERR(0xC00D271EL, "NS_E_DRM_UNABLE_TO_ACQUIRE_LICENSE : The license could not be acquired. Try again later.")// NS_E_DRM_UNABLE_TO_ACQUIRE_LICENSE 
        ERR(0xC00D271FL, "NS_E_DRM_INVALID_LICENSE_ACQUIRED : License acquisition did not work. Acquire a new license or contact the content provider for further assistance.")// NS_E_DRM_INVALID_LICENSE_ACQUIRED 
        ERR(0xC00D2720L, "NS_E_DRM_NO_RIGHTS : The requested operation cannot be performed on this file.")// NS_E_DRM_NO_RIGHTS               
        ERR(0xC00D2721L, "NS_E_DRM_KEY_ERROR : A problem has occurred in the Digital Rights Management component. Contact Microsoft product support..")// NS_E_DRM_KEY_ERROR               
        ERR(0xC00D2722L, "NS_E_DRM_ENCRYPT_ERROR : A problem has occurred in the Digital Rights Management component. Contact Microsoft product support.")// NS_E_DRM_ENCRYPT_ERROR           
        ERR(0xC00D2723L, "NS_E_DRM_DECRYPT_ERROR : The media file is corrupted. Contact the content provider to get a new file.")// NS_E_DRM_DECRYPT_ERROR           
        ERR(0xC00D2724L, "NS_E_DRM_LICENSE_PREVENTS_STORING : You cannot save this file.")// NS_E_DRM_LICENSE_PREVENTS_STORING 
        ERR(0xC00D2725L, "NS_E_DRM_LICENSE_INVALID_XML : The license is corrupted. Acquire a new license.")// NS_E_DRM_LICENSE_INVALID_XML     
        ERR(0x000D2726L, "NS_S_DRM_LICENSE_ACQUIRED : Status message: The license was acquired.")// NS_S_DRM_LICENSE_ACQUIRED        
        ERR(0x000D2727L, "NS_S_DRM_INDIVIDUALIZED : Status message: The security upgrade has been completed.")// NS_S_DRM_INDIVIDUALIZED          
        ERR(0xC00D2728L, "NS_E_DRM_NEEDS_INDIVIDUALIZATION : A security upgrade is required to perform the operation on this media file.")// NS_E_DRM_NEEDS_INDIVIDUALIZATION 
        ERR(0xC00D2729L, "NS_E_DRM_INDIVIDUALIZATION_FAILED : The security upgrade failed. Try again later.")// NS_E_DRM_INDIVIDUALIZATION_FAILED 
        ERR(0xC00D272AL, "NS_E_DRM_ACTION_NOT_QUERIED : The application cannot perform this action. Contact product support for this application.")// NS_E_DRM_ACTION_NOT_QUERIED      
        ERR(0xC00D272BL, "NS_E_DRM_ACQUIRING_LICENSE : You cannot begin a new license acquisition process until the current one has been completed.")// NS_E_DRM_ACQUIRING_LICENSE       
        ERR(0xC00D272CL, "NS_E_DRM_INDIVIDUALIZING : You cannot begin a new security upgrade until the current one has been completed.")// NS_E_DRM_INDIVIDUALIZING         
        ERR(0xC00D272DL, "NS_E_DRM_ENCRYPTING : A problem has occurred in the Digital Rights Management component. Contact Microsoft product support..")// NS_E_DRM_ENCRYPTING              
        ERR(0xC00D272FL, "NS_E_DRM_PARAMETERS_MISMATCHED : A problem has occurred in the Digital Rights Management component. Contact Microsoft product support..")// NS_E_DRM_PARAMETERS_MISMATCHED   
        ERR(0xC00D2730L, "NS_E_DRM_UNABLE_TO_CREATE_LICENSE_OBJECT : A license cannot be created for this media file. Reinstall the application.")// NS_E_DRM_UNABLE_TO_CREATE_LICENSE_OBJECT 
        ERR(0xC00D2731L, "NS_E_DRM_UNABLE_TO_CREATE_INDI_OBJECT : A problem has occurred in the Digital Rights Management component. Contact Microsoft product support..")// NS_E_DRM_UNABLE_TO_CREATE_INDI_OBJECT 
        ERR(0xC00D2732L, "NS_E_DRM_UNABLE_TO_CREATE_ENCRYPT_OBJECT : A problem has occurred in the Digital Rights Management component. Contact Microsoft product support..")// NS_E_DRM_UNABLE_TO_CREATE_ENCRYPT_OBJECT 
        ERR(0xC00D2733L, "NS_E_DRM_UNABLE_TO_CREATE_DECRYPT_OBJECT : A problem has occurred in the Digital Rights Management component. Contact Microsoft product support..")// NS_E_DRM_UNABLE_TO_CREATE_DECRYPT_OBJECT 
        ERR(0xC00D2734L, "NS_E_DRM_UNABLE_TO_CREATE_PROPERTIES_OBJECT : A problem has occurred in the Digital Rights Management component. Contact Microsoft product support..")// NS_E_DRM_UNABLE_TO_CREATE_PROPERTIES_OBJECT 
        ERR(0xC00D2735L, "NS_E_DRM_UNABLE_TO_CREATE_BACKUP_OBJECT : A problem has occurred in the Digital Rights Management component. Contact Microsoft product support..")// NS_E_DRM_UNABLE_TO_CREATE_BACKUP_OBJECT 
        ERR(0xC00D2736L, "NS_E_DRM_INDIVIDUALIZE_ERROR : The security upgrade failed. Try again later.")// NS_E_DRM_INDIVIDUALIZE_ERROR     
        ERR(0xC00D2737L, "NS_E_DRM_LICENSE_OPEN_ERROR : License storage is not working. Contact Microsoft product support.")// NS_E_DRM_LICENSE_OPEN_ERROR      
        ERR(0xC00D2738L, "NS_E_DRM_LICENSE_CLOSE_ERROR : License storage is not working. Contact Microsoft product support.")// NS_E_DRM_LICENSE_CLOSE_ERROR     
        ERR(0xC00D2739L, "NS_E_DRM_GET_LICENSE_ERROR : License storage is not working. Contact Microsoft product support.")// NS_E_DRM_GET_LICENSE_ERROR       
        ERR(0xC00D273AL, "NS_E_DRM_QUERY_ERROR : A problem has occurred in the Digital Rights Management component. Contact Microsoft product support..")// NS_E_DRM_QUERY_ERROR             
        ERR(0xC00D273BL, "NS_E_DRM_REPORT_ERROR : A problem has occurred in the Digital Rights Management component. Contact product support for this application.")// NS_E_DRM_REPORT_ERROR            
        ERR(0xC00D273CL, "NS_E_DRM_GET_LICENSESTRING_ERROR : License storage is not working. Contact Microsoft product support.")// NS_E_DRM_GET_LICENSESTRING_ERROR 
        ERR(0xC00D273DL, "NS_E_DRM_GET_CONTENTSTRING_ERROR : The media file is corrupted. Contact the content provider to get a new file.")// NS_E_DRM_GET_CONTENTSTRING_ERROR 
        ERR(0xC00D273EL, "NS_E_DRM_MONITOR_ERROR : A problem has occurred in the Digital Rights Management component. Try again later.")// NS_E_DRM_MONITOR_ERROR           
        ERR(0xC00D273FL, "NS_E_DRM_UNABLE_TO_SET_PARAMETER : The application has made an invalid call to the Digital Rights Management component. Contact product support for this application.")// NS_E_DRM_UNABLE_TO_SET_PARAMETER 
        ERR(0xC00D2740L, "NS_E_DRM_INVALID_APPDATA : A problem has occurred in the Digital Rights Management component. Contact Microsoft product support..")// NS_E_DRM_INVALID_APPDATA         
        ERR(0xC00D2741L, "NS_E_DRM_INVALID_APPDATA_VERSION : A problem has occurred in the Digital Rights Management component. Contact product support for this application..")// NS_E_DRM_INVALID_APPDATA_VERSION 
        ERR(0xC00D2742L, "NS_E_DRM_BACKUP_EXISTS : Licenses are already backed up in this location.")// NS_E_DRM_BACKUP_EXISTS           
        ERR(0xC00D2743L, "NS_E_DRM_BACKUP_CORRUPT : One or more backed-up licenses are missing or corrupt.")// NS_E_DRM_BACKUP_CORRUPT          
        ERR(0xC00D2744L, "NS_E_DRM_BACKUPRESTORE_BUSY : You cannot begin a new backup process until the current process has been completed.")// NS_E_DRM_BACKUPRESTORE_BUSY      
        ERR(0xC00D2745L, "NS_E_DRM_GET_ATTRIBUTE_ERROR : A problem has occurred in the Digital Rights Management component. Contact product support for this application..")// NS_E_DRM_GET_ATTRIBUTE_ERROR     
        ERR(0x000D2746L, "NS_S_DRM_MONITOR_CANCELLED : Status message: License monitoring has been cancelled.")// NS_S_DRM_MONITOR_CANCELLED       
        ERR(0x000D2747L, "NS_S_DRM_ACQUIRE_CANCELLED : Status message: License acquisition has been cancelled.")// NS_S_DRM_ACQUIRE_CANCELLED       
        ERR(0xC00D2748L, "NS_E_DRM_LICENSE_UNUSABLE : The license is invalid. Contact the content provider for further assistance.")// NS_E_DRM_LICENSE_UNUSABLE        
        ERR(0xC00D2749L, "NS_E_DRM_INVALID_PROPERTY : A required property was not set by the application. Contact product support for this application..")// NS_E_DRM_INVALID_PROPERTY        
        ERR(0xC00D274AL, "NS_E_DRM_SECURE_STORE_NOT_FOUND : A problem has occurred in the Digital Rights Management component of this application. Try to acquire a license again.")// NS_E_DRM_SECURE_STORE_NOT_FOUND  
        ERR(0xC00D274BL, "NS_E_DRM_CACHED_CONTENT_ERROR : A license cannot be found for this media file. Use License Management to transfer a license for this file from the original computer, or acquire a new license.")// NS_E_DRM_CACHED_CONTENT_ERROR    
        ERR(0xC00D274CL, "NS_E_DRM_INDIVIDUALIZATION_INCOMPLETE : A problem occurred during the security upgrade. Try again later.")// NS_E_DRM_INDIVIDUALIZATION_INCOMPLETE 
        ERR(0xC00D274DL, "NS_E_DRM_DRIVER_AUTH_FAILURE : Certified driver components are required to play this media file. Contact Windows Update to see whether updated drivers are available for your hardware.")// NS_E_DRM_DRIVER_AUTH_FAILURE     
        ERR(0xC00D274EL, "NS_E_DRM_NEED_UPGRADE : A new version of the Digital Rights Management component is required. Contact product support for this application to get the latest version.")// NS_E_DRM_NEED_UPGRADE            
        ERR(0xC00D274FL, "NS_E_DRM_REOPEN_CONTENT : Status message: Reopen the file.")// NS_E_DRM_REOPEN_CONTENT          
        ERR(0xC00D2750L, "NS_E_DRM_DRIVER_DIGIOUT_FAILURE : Certain driver functionality is required to play this media file. Contact Windows Update to see whether updated drivers are available for your hardware.")// NS_E_DRM_DRIVER_DIGIOUT_FAILURE  
        ERR(0xC00D2751L, "NS_E_DRM_INVALID_SECURESTORE_PASSWORD : A problem has occurred in the Digital Rights Management component. Contact Microsoft product support..")// NS_E_DRM_INVALID_SECURESTORE_PASSWORD 
        ERR(0xC00D2752L, "NS_E_DRM_APPCERT_REVOKED : A problem has occurred in the Digital Rights Management component. Contact Microsoft product support..")// NS_E_DRM_APPCERT_REVOKED         
        ERR(0xC00D2753L, "NS_E_DRM_RESTORE_FRAUD : You cannot restore your license(s).")// NS_E_DRM_RESTORE_FRAUD           
        ERR(0xC00D2754L, "NS_E_DRM_HARDWARE_INCONSISTENT : The licenses for your media files are corrupted. Contact Microsoft product support.")// NS_E_DRM_HARDWARE_INCONSISTENT   
        ERR(0xC00D2755L, "NS_E_DRM_SDMI_TRIGGER : To transfer this media file, you must upgrade the application.")// NS_E_DRM_SDMI_TRIGGER            
        ERR(0xC00D2756L, "NS_E_DRM_SDMI_NOMORECOPIES : You cannot make any more copies of this media file.")// NS_E_DRM_SDMI_NOMORECOPIES       
        ERR(0xC00D2763L, "NS_E_DRM_UNABLE_TO_CREATE_AUTHENTICATION_OBJECT : A problem has occurred in the Digital Rights Management component. Contact Microsoft product support..")// NS_E_DRM_UNABLE_TO_CREATE_AUTHENTICATION_OBJECT 
        ERR(0x000D2AF8L, "NS_S_REBOOT_RECOMMENDED : The requested operation is successful.  Some cleanup will not be complete until the system is rebooted.")// NS_S_REBOOT_RECOMMENDED          
        ERR(0x000D2AF9L, "NS_S_REBOOT_REQUIRED : The requested operation is successful.  The system will not function correctly until the system is rebooted.")// NS_S_REBOOT_REQUIRED             
        ERR(0xC00D2AFAL, "NS_E_REBOOT_RECOMMENDED : The requested operation failed.  Some cleanup will not be complete until the system is rebooted.")// NS_E_REBOOT_RECOMMENDED          
        ERR(0xC00D2AFBL, "NS_E_REBOOT_REQUIRED : The requested operation failed.  The system will not function correctly until the system is rebooted.")// NS_E_REBOOT_REQUIRED             
        ERR(0xC00D2EE0L, "NS_E_UNKNOWN_PROTOCOL : The specified protocol is not supported.")// NS_E_UNKNOWN_PROTOCOL            
        ERR(0xC00D2EE1L, "NS_E_REDIRECT_TO_PROXY : The client is redirected to a proxy server.")// NS_E_REDIRECT_TO_PROXY           
        ERR(0xC00D2EE2L, "NS_E_INTERNAL_SERVER_ERROR : The server encountered an unexpected condition which prevented it from fulfilling the request.")// NS_E_INTERNAL_SERVER_ERROR       
        ERR(0xC00D2EE3L, "NS_E_BAD_REQUEST : The request could not be understood by the server.")// NS_E_BAD_REQUEST                 
        ERR(0xC00D2EE4L, "NS_E_ERROR_FROM_PROXY : The proxy experienced an error while attempting to contact the media server.")// NS_E_ERROR_FROM_PROXY            
        ERR(0xC00D2EE5L, "NS_E_PROXY_TIMEOUT : The proxy did not receive a timely response while attempting to contact the media server.")// NS_E_PROXY_TIMEOUT               
        ERR(0xC00D2EE6L, "NS_E_SERVER_UNAVAILABLE : The server is currently unable to handle the request due to a temporary overloading or maintenance of the server.")// NS_E_SERVER_UNAVAILABLE          
        ERR(0xC00D2EE7L, "NS_E_REFUSED_BY_SERVER : The server is refusing to fulfill the requested operation.")// NS_E_REFUSED_BY_SERVER           
        ERR(0xC00D2EE8L, "NS_E_INCOMPATIBLE_SERVER : The server is not a compatible streaming media server.")// NS_E_INCOMPATIBLE_SERVER         
        ERR(0xC00D2EE9L, "NS_E_MULTICAST_DISABLED : The content cannot be streamed because the Multicast protocol has been disabled.")// NS_E_MULTICAST_DISABLED          
        ERR(0xC00D2EEAL, "NS_E_INVALID_REDIRECT : The server redirected the player to an invalid location.")// NS_E_INVALID_REDIRECT            
        ERR(0xC00D2EEBL, "NS_E_ALL_PROTOCOLS_DISABLED : The content cannot be streamed because all protocols have been disabled.")// NS_E_ALL_PROTOCOLS_DISABLED      
        ERR(0xC00D2EECL, "NS_E_MSBD_NO_LONGER_SUPPORTED : The MSBD protocol is no longer supported. Please use HTTP to connect to the Windows Media stream.")// NS_E_MSBD_NO_LONGER_SUPPORTED    
        ERR(0xC00D2EEDL, "NS_E_PROXY_NOT_FOUND : The proxy server could not be located. Please check your proxy server configuration.")// NS_E_PROXY_NOT_FOUND             
        ERR(0xC00D2EEEL, "NS_E_CANNOT_CONNECT_TO_PROXY : Unable to establish a connection to the proxy server. Please check your proxy server configuration.")// NS_E_CANNOT_CONNECT_TO_PROXY     
        ERR(0xC00D2EEFL, "NS_E_SERVER_DNS_TIMEOUT : Unable to locate the media server. The operation timed out.")// NS_E_SERVER_DNS_TIMEOUT          
        ERR(0xC00D2EF0L, "NS_E_PROXY_DNS_TIMEOUT : Unable to locate the proxy server. The operation timed out.")// NS_E_PROXY_DNS_TIMEOUT           
        ERR(0xC00D2EF1L, "NS_E_CLOSED_ON_SUSPEND : Media closed because Windows was shut down.")// NS_E_CLOSED_ON_SUSPEND           

        /*
            DIRECT SOUND ERRORS.
        */

        ERR(MAKE_HRESULT(1, 0x878, 10), "DSERR_ALLOCATED The call failed because resources (such as a priority level) were already being used by another caller")// %2 %1
        ERR(MAKE_HRESULT(1, 0x878, 30), "DSERR_CONTROLUNAVAIL The control (vol, pan, etc.) requested by the caller is not available")// %2 %1
        ERR(MAKE_HRESULT(1, 0x878, 50), "DSERR_INVALIDCALL This call is not valid for the current state of this object")// %2 %1
        ERR(MAKE_HRESULT(1, 0x878, 70), "DSERR_PRIOLEVELNEEDED The caller does not have the priority level required for the function to succeed")// %2 %1
        ERR(MAKE_HRESULT(1, 0x878, 100), "DSERR_BADFORMAT The specified WAVE format is not supported")// %2 %1
        ERR(MAKE_HRESULT(1, 0x878, 120), "DSERR_NODRIVER No sound driver is available for use")// %2 %1
        ERR(MAKE_HRESULT(1, 0x878, 130), "DSERR_ALREADYINITIALIZED This object is already initialized")// %2 %1
        ERR(MAKE_HRESULT(1, 0x878, 150), "DSERR_BUFFERLOST The buffer memory has been lost, and must be restored")// %2 %1
        ERR(MAKE_HRESULT(1, 0x878, 160), "DSERR_OTHERAPPHASPRIO Another app has a higher priority level, preventing this call from succeeding")// %2 %1
        ERR(MAKE_HRESULT(1, 0x878, 170), "DSERR_UNINITIALIZED This object has not been initialized")// %2 %1
        ERR(MAKE_HRESULT(1, 0x878, 190), "DSERR_DS8_REQUIRED Attempt to use DirectSound 8 functionality on an older DirectSound object")// %2 %1
        ERR(MAKE_HRESULT(1, 0x878, 200), "DSERR_SENDLOOP A circular loop of send effects was detected")// %2 %1
        ERR(MAKE_HRESULT(1, 0x878, 210), "DSERR_BADSENDBUFFERGUID The GUID specified in an audiopath file does not match a valid MIXIN buffer")// %2 %1
        ERR(MAKE_HRESULT(1, 0x878, 353), "DSERR_OBJECTNOTFOUND The object requested was not found (numerically equal to DMUS_E_NOT_FOUND)")// %2 %1
    default:
        Buf->FormatW(L"(Unknown error): 0x%08x (%d)", hr, hr);
        break;
    }
#endif
}

