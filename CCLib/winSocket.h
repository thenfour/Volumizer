/*******************************************
 * winSocket.h - Header file for winSocket * 
 *      Winsock API wrapper class          *
 *    Ryan Lederman ryan@winprog.org       *
 *            February 2001                *
 *       _THIS CODE IS FREEWARE_           *
 *                                         *
 *******************************************/


#define WM_WINSOCKEVENT (WM_USER+1)

#include "winsock.h"
#include "winbase.h"


#define WIN32_LEAN_AND_MEAN
#define ERR_SUCCESS 0	// Successfull
#define ERR_BADPARAM 1	// Bad argument passed
#define ERR_WSAERROR 2	// Need to get_LastError()
#define ERR_MAXLENGTH 512


class CCEXPORT winSocket	// Definition of winSocket
{
public:	// Public Methods
	winSocket::winSocket();		// Constructor
	winSocket::~winSocket();	// Destructor

	virtual int winSocket::Create( void );	// Creates the socket
	int winSocket::Close( void );		// Closes the socket
	int winSocket::Connect( char* strRemote, unsigned int iPort );	// Connects the socket to a remote site
	int winSocket::Send( char* strData, int iLen );	// Sends data
	int winSocket::Receive( SOCKET s, char* strData, int iLen ); // Receives data
	int winSocket::Listen( int iQueuedConnections );	// Listen for connections
	int winSocket::Bind( char* strIP, unsigned int iPort );	// Binds to a port
	int winSocket::Accept( SOCKET s );	// Accepts a connection
	int winSocket::asyncSelect( HWND hWnd,	// Allows calling window to receive 
		unsigned int wMsg, long lEvent );	// notifications (non-blocking sockets)										
	int get_LocalIP( char* strIP );		// Returns local IP address			
	int get_LocalPort( int* iPort );	// Returns local Port number
	int get_RemoteIP( char* strIP );	// Returns remote side IP
	int get_RemotePort( int* iPort );	// Returns remote side Port number
	int get_LocalHost( char* strBuffer, int iBufLen );	// Returns local host name
	int get_RemoteHost( char* strBuffer, int iBufLen );	// Returns remote host name
	void winSocket::get_LastError( char* strBuffer, int* iErrNum );	// Returns error information
	void winSocket::longToDottedQuad( unsigned long ulLong, char* cBuffer );	// 32-bit long -> dotted quad
private:	// Private Methods
	void winSocket::set_LastError( char* newError, int errNum );	// Sets last error information
private:	// Private Members
	struct sockaddr_in m_sockaddr;	// Holds all data associated with socket
	struct sockaddr_in m_rsockaddr;	// Holds data associated with remote side
	WORD m_wVersion;	// Version to use when calling WSAStartup
	char m_LastError[ERR_MAXLENGTH+1];	// Buffer that holds last error
	int	 m_ErrorNumber;		// Last error number
public:		// Public Members
	SOCKET m_hSocket;	// Underlying SOCKET object
};