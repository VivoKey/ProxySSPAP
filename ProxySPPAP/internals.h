#pragma once

#include <Windows.h>
#include <logger.h>
#include "package.h"

////////////////////////////////////////////////////////////////
/////				����������� MACRO					////////
////////////////////////////////////////////////////////////////

/// ��������� ���� � 4 ���������
/// �������� ���� ������� ����������� ���� ������� ����� ����� ����������
#define HEAP_SIZE 0x1000

/// <summary>
/// �������� LSA ������� �� ������� �������
/// </summary>
#define LSA_CALL(f, ... )  \
	pLsaDispatch->f( ##__VA_ARGS__ )

#pragma region LSA_FUNCTION_POINTERS
/// <summary>
/// �������� ������ � ����. ���������, ��� ��������� ������, ���������� ������� � LSA, ����� ������������ � �������������� ���� �������.
/// ������, ���������� ���� ����������, ������ ���� ����������� � ������� ������� FreeLsaHeap.
/// </summary>
#define LSA_ALLOCATE_HEAP(LA)						LSA_CALL(AllocateLsaHeap, (LA))

/// <summary>
/// �������� ������ �� ������ ����.
/// ������, ���������� ���� ����������, ������ ���� ����������� � ������� ������� FreePrivateHeap.
/// </summary>
#define LSA_ALLOCATE_PRIVATE_HEAP_F(LA)				LSA_CALL(AllocatePrivateHeap, (LA))

/// <summary>
/// ����������� ������, ���������� � ������� ������� AllocatePrivateHeap.
/// </summary>
#define LSA_FREE_PRIVATE_HEAP_F(PV)					LSA_CALL(FreePrivateHeap, (PV))

/// <summary>
/// ����������� ������ �� ����, ���������� ����� ����� AllocateLsaHeap.
/// </summary>
#define LSA_FREE_HEAP(PV)							LSA_CALL(FreeLsaHeap, (PV))

/// <summary>
/// �������� ����� � �������� ������������ �������. ������, ���������� � �������� ������������ �������,
/// ������������ ��� �������� ����������, ������������ ������� �� ������ �������� �����������.
/// </summary>
#define LSA_ALLOCATE_CLIENT_BUFFER_F(CR, LR, CBA)	LSA_CALL(AllocateClientBuffer, (CR), (LR), (CBA))

/// <summary>
/// �������� ���������� �� ������ � ������� �������� � �������� ������������ ����������� ��������.
/// </summary>
#define LSA_COPY_TO_CLIENT_BUFFER_F(CR,L,CBA,BTC)	LSA_CALL(CopyToClientBuffer, (CR), L, CBA, BTC)

/// <summary>
/// ����������� �����, ����� ���������� �������� AllocateClientBuffer.
/// </summary>
#define LSA_FREE_CLIENT_BUFFER_F(CR,CBA)			LSA_CALL(FreeClientBuffer, (CR), (CBA))

/// <summary>
/// ������� GetCallInfo ��������� ���������� � ��������� ������ �������.
/// </summary>
#define LSA_GET_CALL_INFO_F(PV)						LSA_CALL(GetCallInfo, (PV))

/// <summary>
/// �������� ���������� ������� ������ ������������ � ���� ������ ���������� ������� ������� ������������ (SAM).
/// </summary>
/// <params>
/// _In_ PSECURITY_STRING Name,
/// _In_ SECPKG_NAME_TYPE NameType,
/// _In_ PSECURITY_STRING Prefix,
/// _In_ BOOLEAN AllowGuest,
/// _In_ ULONG Reserved,
/// _Out_ PVOID * UserHandle
/// </params>
#define LSA_OPEN_SAM_USER_F(N,NT,P,AG,R,US)			LSA_CALL(OpenSamUser, N,NT,P,AG,R,US)

/// <summary>
/// ������� GetUserAuthData ���������� ������ ����������� ��� ������������ � ����� ������.
/// </summary>
#define LSA_GET_USER_AUTH_DATA_F(UH,UAD,UADS)		LSA_CALL(GetUserAuthData, (UH),(UAD),(UserAuthDataSize))

/// <summary>
/// ������� GetAuthDataForUser ��������� ������ �������������� ��� ������������ 
/// �� ���� ������ ���������� ������� ������� ������������ (SAM) � �������� �� � ������, ���������� ��� ������� ConvertAuthDataToToken .
/// </summary>
#define LSA_GET_AUTH_DATA_FOR_USER_F(N,NT,P,AG,R,U) LSA_CALL(GetAuthDataForUser, (N),(NT),(P),(AG),(R),(U))

/// <summary>
/// ������� CloseSamUser ��������� ���������� ������� ������ ������������ ���������� ������� ������� ������������ (SAM).
/// </summary>
#define LSA_CLOSE_SAM_USER_F(PV)					LSA_CALL(CloseSamUser,(UserHandle))

/// <summary>
/// ������� ImpersonateClient ���������� ��� ������������� ������������.
/// </summary>
#define LSA_IMPERSONATE_CLIENT_F()					LSA_CALL(ImpersonateClient)

/// <summary>
/// ������� ������ ����� � �������.
/// ����� ����� � ������� ���������������� ���������� ��������������� �����(LUID), ����������� ������ ����� � �������.
/// </summary>
#define LSA_CREATE_LOGON_SESSION_F(LID)				LSA_CALL(CreateLogonSession, LID)

/// <summary>
/// ������� ��� ������ ����� � �������, ��������� ��� ����������� ����, �������� �� ���������� �������������� ������������ ������.
/// </summary>
#define LSA_DELETE_LOGON_SESSION_F(LID)				LSA_CALL(DeleteLogonSession, LID)

#pragma endregion

////////////////////////////////////////////////////////////////
/////				����������� FUNC					////////
////////////////////////////////////////////////////////////////

/* �������� ������ ��� LSA_STRING*/
LSA_STRING *AllocateLsaStringLsa(
	LPCSTR szString
);

/* �������� ������ ��� UNICODE_STRING*/
UNICODE_STRING *AllocateUnicodeStringLsa(
	LPCWSTR szString
);

/* �������� ����� ������ �� ����������� ����������� �����*/
LPVOID LsaAllocateHeap(
	ULONG size,
	LPBYTE * ppHeapBase,
	LPBYTE * ppHeapPtr
);

/* ��������� �� ������� ������� */
extern PLSA_DISPATCH_TABLE pLsaDispatch;

/* ��������� ����������� ������ */
extern HMODULE MsvPackage;

/*  */
extern PSECPKG_FUNCTION_TABLE pMsvTables;

/*  */
extern PLSA_AP_INITIALIZE_PACKAGE MsvLsaApInitializePackage;

/*  */
extern PLSA_AP_LOGON_TERMINATED MsvLsaApLogonTerminated;

/*  */
extern PLSA_AP_LOGON_USER_EX2  MsvLsaApLogonUserEx2;
