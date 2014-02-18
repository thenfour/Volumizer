/*******************************************
 *   winSocket.cpp - Implementation of     * 
 *   winSocket Winsock API wrapper class   *
 *    Ryan Lederman ryan@winprog.org       *
 *            February 2001                *
 *       _THIS CODE IS FREEWARE_           *
 *                                         *
 *******************************************/

#include "stdafx.h"
#include "winSocket.h"
#include <stdio.h>

winSocket::winSocket() : m_hSocket(0),
                         m_wVersion(0),
                         m_ErrorNumber(0)		
{
	WSADATA wsaD;	// Structure initialsed by WSAStartup
	m_wVersion = MAKEWORD(2,2);	// Version number requested

	memset( m_LastError, 0, ERR_MAXLENGTH );	// Nullify last error
	memset( &m_sockaddr, 0, sizeof( m_sockaddr ) );	// Nullify structures
	memset( &m_rsockaddr, 0, sizeof( m_rsockaddr ) );

	int result = WSAStartup( m_wVersion, &wsaD );	// Initialize Winsock
	
	if( result != 0 ) // WSAStartup failed
	{
        set_LastError( "WSAStartup failed!", WSAGetLastError() );
        return;
	}
}

winSocket::~winSocket() { WSACleanup();	/* Un-initialise Winsock*/ }

int winSocket::Create( void )
{
	/**************************************
	* FUNCTION: Create                    *
	*                                     *
	* PURPOSE: Initializes the underlying *
	* SOCKET object for the class.        *           
	*                                     * 
	* RETURNS: ERR_WSAERROR upon error,   *                 
	* otherwise ERR_SUCCESS               *   
	*                                     *
	***************************************/

	if ( (m_hSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP )) == INVALID_SOCKET )
	{
        set_LastError( "socket() failed", WSAGetLastError() );
        return ERR_WSAERROR;
	}

	return ERR_SUCCESS;	
}

int winSocket::Close( void )
{
	/****************************************
	* FUNCTION: Close                       *
	*                                       *
	* PURPOSE: Closes the underlying        *
	* SOCKET object. Does not destroy class *           
	*                                       * 
	* RETURNS: ERR_WSAERROR upon error,     *                  
	* otherwise ERR_SUCCESS                 *   
	*                                       *
	*****************************************/

	if ( closesocket( m_hSocket ) == SOCKET_ERROR )
	{
        set_LastError( "closesocket() failed", WSAGetLastError() );
        return ERR_WSAERROR;
	}

	return ERR_SUCCESS;
}

int winSocket::Connect( char* strRemote, unsigned int iPort )
{
	/*****************************************
	* FUNCTION: Connect                      *
	*                                        *
	* PURPOSE: Establishes TCP/IP connection *
	* with remote host (strRemote) on port   *     
	* # (iPort)                              *
	*                                        *
	* RETURNS: ERR_BADPARAM for invalid      *
	* parameters, ERR_WSAERROR upon error,   *
	* otherwise ERR_SUCCESS                  *
	*                                        *
	******************************************/

	if( strlen( strRemote ) == 0 || iPort == 0 )
		return ERR_BADPARAM;

	hostent *hostEnt = NULL;
	long lIPAddress = 0;

	hostEnt = gethostbyname( strRemote );

	if( hostEnt != NULL )
	{
		lIPAddress = ((in_addr*)hostEnt->h_addr)->s_addr;
		m_sockaddr.sin_addr.s_addr = lIPAddress;
	}
	else
	{
		m_sockaddr.sin_addr.s_addr = inet_addr( strRemote );
	}

	m_sockaddr.sin_family = AF_INET;
	m_sockaddr.sin_port = htons( iPort );

	if( connect( m_hSocket, (SOCKADDR*)&m_sockaddr, sizeof( m_sockaddr ) ) == SOCKET_ERROR )
	{
        set_LastError( "connect() failed", WSAGetLastError() );
        return ERR_WSAERROR;
	}

	return ERR_SUCCESS;
}

int winSocket::Listen( int iQueuedConnections )
{
	/*****************************************
	* FUNCTION: Listen                       *
	*                                        *
	* PURPOSE: Places the SOCKET in the      *
	* listening state. Requires that Bind()  *
	* be called previously.                  *
	*                                        *
	* RETURNS: ERR_BADPARAM for invalid      *
	* parameters, ERR_WSAERROR upon error,   *
	* otherwise ERR_SUCCESS                  *
	*                                        *
	******************************************/

	if( iQueuedConnections == 0 )
		return ERR_BADPARAM;

	if( listen( m_hSocket, iQueuedConnections ) == SOCKET_ERROR )
	{
        set_LastError( "listen() failed", WSAGetLastError() );
        return ERR_WSAERROR;
	}

	return ERR_SUCCESS;
}

int winSocket::Send( char* strData, int iLen )
{
	/**********************************************
	* FUNCTION: Send                              *
	*                                             *
	* PURPOSE: Sends data (strData) to remote     *
	* side on an established TCP/IP connection.   *
	* Requires that Connect be called previously. *
	*                                             *
	* RETURNS: ERR_BADPARAM for invalid           *
	* parameters, ERR_WSAERROR upon error,        *
	* otherwise ERR_SUCCESS                       *
	*                                             *
	***********************************************/

	if( strData == NULL || iLen == 0 )
		return ERR_BADPARAM;

	if( send( m_hSocket, strData, iLen, 0 ) == SOCKET_ERROR )
	{
        set_LastError( "send() failed", WSAGetLastError() );
        return ERR_WSAERROR;
	}
	
	return ERR_SUCCESS;
}

int winSocket::Receive( SOCKET s, char* strData, int iLen )
{
	/***********************************************
	* FUNCTION: Receive                            *
	*                                              *
	* PURPOSE: Retreives data from incoming queue  *
	* and copies to (strData). (iLen) will contain *
	* the length of data read in bytes             *
	*                                              *
	* RETURNS: ERR_BADPARAM for invalid            *
	* parameters, ERR_WSAERROR upon error,         *
	* otherwise passes what recv() returns.        *
	*                                              *
	***********************************************/

	if( strData == NULL )
		return ERR_BADPARAM;

	int len = 0;
	int ret = 0;
	
	ret = recv( s, strData, iLen, 0 );

	if ( ret == SOCKET_ERROR )
	{
        set_LastError( "recv() failed", WSAGetLastError() );
        return ERR_WSAERROR;
	}
	return ret;
}

int winSocket::Bind( char* strIP, unsigned int iPort )
{
	/************************************************
	* FUNCTION: Bind                                *
	*                                               *
	* PURPOSE: Associates the SOCKET object with an *
	* IP address (strIP) and port number (iPort)    *
	*                                               *
	* RETURNS: ERR_BADPARAM for invalid             *
	* parameters, ERR_WSAERROR upon error,          *
	* otherwise ERR_SUCCESS                         *
	*                                               *
	************************************************/

	if( strlen( strIP ) == 0 || iPort == 0 )
		return ERR_BADPARAM;

	memset( &m_sockaddr,0, sizeof( m_sockaddr ) );
	m_sockaddr.sin_family = AF_INET;
	m_sockaddr.sin_addr.s_addr = inet_addr( strIP );
	m_sockaddr.sin_port = htons( iPort );

	if ( bind( m_hSocket, (SOCKADDR*)&m_sockaddr, sizeof( m_sockaddr ) ) == SOCKET_ERROR )
	{
        set_LastError( "bind() failed", WSAGetLastError() );
        return ERR_WSAERROR;
	}
	return ERR_SUCCESS;
}

int winSocket::Accept( SOCKET s )
{	
	/***************************************************
	* FUNCTION: Accept                                 *
	*                                                  *
	* PURPOSE: Initializes the SOCKET object (if not   *
	* previously initialized), associates the SOCKET   *
	* object with the IP address and port of the       *
	* remote side, and accepts an incoming connection. *
	* Usually called from a Window Procedure using     *
	* wParam as the argument.                          *
	*                                                  *
	* RETURNS: ERR_WSAERROR upon error,                *
	* otherwise ERR_SUCCESS                            *
	*                                                  *
	****************************************************/

	int Len = sizeof( m_rsockaddr );

	memset( &m_rsockaddr, 0, sizeof( m_rsockaddr ) );

	if( ( m_hSocket = accept( s, (SOCKADDR*)&m_rsockaddr, &Len ) ) == INVALID_SOCKET )
	{
        set_LastError( "accept() failed", WSAGetLastError() );
        return ERR_WSAERROR;
	}

	return ERR_SUCCESS;
}

int winSocket::asyncSelect( HWND hWnd, unsigned int wMsg, long lEvent )
{
	/**************************************************
	* FUNCTION: asyncSelect                           *
	*                                                 *
	* PURPOSE: Enables Windows Messaging notification *
	* for the object. (wMsg) will be sent to the      *
	* Window Procedure of (hWnd) whenever one of the  *
	* events in (lEvent) has occurred. See MSDN docs  *
	* for WSAAsyncSelect() for more information.	  *
	*                                                 *
	* RETURNS: ERR_BADPARAM for invalid               *
	* parameters, ERR_WSAERROR upon error,            *
	* otherwise ERR_SUCCESS                           *
	*                                                 *
	***************************************************/

	if( !IsWindow( hWnd ) )
        return ERR_BADPARAM;

	if( WSAAsyncSelect( m_hSocket, hWnd, wMsg, lEvent ) == SOCKET_ERROR )
	{
        set_LastError( "WSAAsyncSelect() failed", WSAGetLastError() );
        return ERR_WSAERROR;
	}
	return ERR_SUCCESS;
}

int winSocket::get_RemoteIP( char* strIP )
{
	/*************************************************
	* FUNCTION: get_RemoteIP                         *
	*                                                *
	* PURPOSE: Copies the IP address for the remote  *
	* side on an established TCP/IP connection into  *
	* (strIP).                                       *
	*                                                *
	* RETURNS: ERR_BADPARAM for invalid parameters,  *
	* ERR_WSAERROR upon error, otherwise ERR_SUCCESS *
	*                                                *
	**************************************************/

	if( strIP == NULL )
        return ERR_BADPARAM;

	int namelen = sizeof( m_rsockaddr );

	if( getpeername( m_hSocket, (SOCKADDR*)&m_rsockaddr, &namelen ) == SOCKET_ERROR )
	{
        set_LastError( "getpeername() failed", WSAGetLastError() );
        return ERR_WSAERROR;
	}

	longToDottedQuad( m_rsockaddr.sin_addr.s_addr, strIP );

	return ERR_SUCCESS;
}

int winSocket::get_RemotePort( int* iPort )
{
	/*************************************************
	* FUNCTION: get_RemotePort                       *
	*                                                *
	* PURPOSE: Copies the port number for the remote *
	* side on an established TCP/IP connection into  *
	* (iPort).                                       *
	*                                                *
	* RETURNS: ERR_BADPARAM for invalid parameters,  *
	* ERR_WSAERROR upon error, otherwise ERR_SUCCESS *
	*                                                *
	**************************************************/

	if( iPort == NULL )
		return ERR_BADPARAM;

	int namelen = sizeof( m_rsockaddr );
	
	if( getpeername( m_hSocket, (SOCKADDR*)&m_rsockaddr, &namelen ) == SOCKET_ERROR )
	{
        set_LastError( "getpeername() failed", WSAGetLastError() );
        return ERR_WSAERROR;
	}

	*iPort = ntohs( m_rsockaddr.sin_port );

	return ERR_SUCCESS;
}

int winSocket::get_LocalHost( char* strBuffer, int iBufLen )
{
	/*************************************************
	* FUNCTION: get_LocalHost                        *
	*                                                *
	* PURPOSE: Copies the fully qualified host name  *
	* for the local machine into (strBuffer). Will   *
	* fail if returned data is longer than (iBufLen).*
	*                                                *
	* RETURNS: ERR_BADPARAM for invalid parameters,  *
	* ERR_WSAERROR upon error, otherwise ERR_SUCCESS *
	*                                                *
	**************************************************/

	if( strBuffer == NULL )
		return ERR_BADPARAM;

	char strHost[512] = {0};
	hostent* hostEnt = NULL;
	int iLen = 0;

	gethostname( strHost, 512 );
	hostEnt = gethostbyname( strHost );

	if( hostEnt == NULL )
		return ERR_WSAERROR;

	iLen = strlen( hostEnt->h_name );

	if( iLen > iBufLen )
		return ERR_BADPARAM;

	memset( strBuffer, 0, iBufLen );
	memcpy( strBuffer, hostEnt->h_name, iLen );

	return ERR_SUCCESS;
}

int winSocket::get_RemoteHost( char* strBuffer, int iBufLen )
{
	/*************************************************
	* FUNCTION: get_RemoteHost                       *
	*                                                *
	* PURPOSE: Copies the fully qualified host name  *
	* of the remote side (on a connected socket)     *
	* into (strBuffer). Will fail if data returned   *
	* is longer than iBufLen.                        *
	*                                                *
	* RETURNS: ERR_BADPARAM for invalid parameters,  *
	* ERR_WSAERROR upon error, otherwise ERR_SUCCESS *
	*                                                *
	**************************************************/

	if( strBuffer == NULL )
		return ERR_BADPARAM;

	hostent* hostEnt = NULL;
	int iLen = 0;
	int namelen = sizeof( m_rsockaddr );

	if( getpeername( m_hSocket, (SOCKADDR*)&m_rsockaddr, &namelen ) == SOCKET_ERROR )
		return ERR_WSAERROR;

	hostEnt = gethostbyaddr( (char*)&m_rsockaddr.sin_addr.s_addr, 4 ,PF_INET );

	if( hostEnt != NULL )
	{
		iLen = strlen( hostEnt->h_name );
		if( iLen > iBufLen )
			return ERR_BADPARAM;

		memcpy( strBuffer, hostEnt->h_name, iLen );
		return ERR_SUCCESS;
	}

	return ERR_WSAERROR;
}

int winSocket::get_LocalIP( char* strIP )
{
	/*************************************************
	* FUNCTION: get_LocalIP                          *
	*                                                *
	* PURPOSE: Copies the IP address for the local   *
	* machine into (strIP). Requires that Connect or *
	* Bind be called previously                      *
	*                                                *
	* RETURNS: ERR_BADPARAM for invalid parameters,  *
	* otherwise ERR_SUCCESS                          *
	*                                                *
	**************************************************/

	if( strIP == NULL )
		return ERR_BADPARAM;
	
	int  namelen = sizeof( m_sockaddr );
	HOSTENT* hEnt = NULL;
	char szHostName[512] = {0};
	char szIP[16] = {0};
	char szAddrField[4] = {0};
	unsigned int ufield = 0;

	if( getsockname( m_hSocket, (SOCKADDR*)&m_sockaddr, &namelen ) == SOCKET_ERROR )
		return ERR_WSAERROR;

	longToDottedQuad( m_sockaddr.sin_addr.s_addr, strIP );

	return ERR_SUCCESS;
}

int winSocket::get_LocalPort( int* iPort )
{
	/*****************************************************
	* FUNCTION: get_LocalPort                            *
	*                                                    *
	* PURPOSE: Copies the local port number associated   *
	* with the SOCKET object into (iPort).               *
	* Requires that Connect or Bind be called previously *
	*                                                    *
	* RETURNS: ERR_BADPARAM for invalid parameters,      *
	* otherwise ERR_SUCCESS                              *
	*                                                    *
	******************************************************/

	if( iPort == NULL )
        return ERR_BADPARAM;

	*iPort = ntohs(m_sockaddr.sin_port);

	return ERR_SUCCESS;
}

void winSocket::set_LastError( char* newError, int errNum )
{
	/**************************************************
	* FUNCTION: set_LastError                         *
	*                                                 *
	* PURPOSE: Sets error information for the object. *
	*                                                 *
	* RETURNS: None.                                  *
	*                                                 *
	***************************************************/

	memset( m_LastError, 0, ERR_MAXLENGTH ); 
	memcpy( m_LastError, newError, strlen( newError ) );
	m_LastError[strlen(newError)+1] = '\0';
	m_ErrorNumber = errNum;
}

void winSocket::get_LastError( char* strBuffer, int* iErrNum )
{
	/***************************************************
	* FUNCTION: get_LastError                          *
	*                                                  *
	* PURPOSE: Retreives description and number of the *
	* last error that occurred. Copies into (strBuffer)*
	* and (iErrNum), repsectively.                     *
	*                                                  *
	* RETURNS: None.                                   *
	*                                                  *
	****************************************************/

	int len = strlen( m_LastError );

	if( len > 0 )
	{
        memset( strBuffer, 0, len );
        memcpy( strBuffer, m_LastError, len );
        strBuffer[len+1] = '\0';
        *iErrNum = m_ErrorNumber;
	}
}

void winSocket::longToDottedQuad( unsigned long ulLong, char* cBuffer )
{
	/*****************************************************
	* FUNCTION: longToDottedQuad                         *
	*                                                    *
	* PURPOSE: Translates an IP address from 32-bit long *
	* to dotted quad form (255.255.255.255). Translates  *
	* (ulLong) and copies results to (cBuffer).          *
	*                                                    *
	* RETURNS: None.                                     *
	*                                                    *
	******************************************************/

	sprintf(cBuffer, "%d.%d.%d.%d",(int)((BYTE*)&ulLong)[0],
		(int)((BYTE*)&ulLong)[1],(int)((BYTE*)&ulLong)[2],(int)((BYTE*)&ulLong)[3] );
}


