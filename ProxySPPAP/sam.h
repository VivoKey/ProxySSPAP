#ifndef SAM_USER_TOKEN_INFO_H
#define SAM_USER_TOKEN_INFO_H

#pragma once
#include "internals.h"
#include <LM.h>

/// <summary>����� ��� ��������� ������.</summary>
typedef HANDLE OEM_SAM_HANDLE;
typedef OEM_SAM_HANDLE *POEM_SAM_HANDLE;

/// <summary>�������������� ������� ��������� � samlib.</summary>
NTSTATUS SamAllocateResource(VOID);

/// <summary>����������� ������� ��������� � samlib.</summary>
VOID SamFreeResource(VOID);

/// <summary>��������� ���������� � �� SAM.</summary>
_Check_return_ NTSTATUS NTAPI InitSamDatabase(
	_Out_ POEM_SAM_HANDLE pSamTokenHandler, LPCWSTR pwsDomain
);

/// <summary>
/// ������������� �������� �����������. � ������ �������������� �������� ����� ���������� ��� ����������� �������� ������������.
/// ������� �������� � <param>OEM_SAM_HANDLE</param>.
/// </summary>
/// <remarks>������� ����� ����������� ��������� � �������� ������������, 
/// ��� ��� ���������� � �� SAN ����� ������� ��� �������������:<function>InitSamDatabase</function>.
/// �.�. ������������ ���� � ��� �� �������  <param>OEM_SAM_HANDLE</param> ��� ������ ���������� ������ �� �������������.
/// </remarks>
/// <todo>������� � ��������� �������� ������� ������������.</todo>
_Check_return_ NTSTATUS NTAPI SetupUserContext(
	_In_ OEM_SAM_HANDLE hSamTokenHandler,
	_In_ LPCWSTR psuUsername
);

/// <summary>
/// ������� ����� ������������� ���������� ����
/// </summary>
/// <remarks>
/// ������ 1. �������������� ������ ��������� LSA_TOKEN_INFORMATION_V2.
/// ������ ������ ���� ��������� � ����������� �����
/// </remarks>
_Check_return_ NTSTATUS NTAPI AllocateTokenInformation(
	_In_ OEM_SAM_HANDLE pSamTokenHandler,
	_In_ LSA_TOKEN_INFORMATION_TYPE tokenInforamtionType,
	_When_(tokenInforamtionType == LsaTokenInformationNull, _Out_bytecapcount_(sizeof(LSA_TOKEN_INFORMATION_NULL)))
	_When_(tokenInforamtionType == LsaTokenInformationV1, _Out_bytecapcount_(sizeof(LSA_TOKEN_INFORMATION_V1)))
	_When_(tokenInforamtionType == LsaTokenInformationV2, _Out_bytecapcount_(sizeof(LSA_TOKEN_INFORMATION_V2)))
	_When_(tokenInforamtionType == LsaTokenInformationV3, _Out_bytecapcount_(sizeof(LSA_TOKEN_INFORMATION_V3)))
	PVOID * tokenInformation
);

/// <summary>
/// ������� ������� ������������
/// </summary>
/// <remarks>
/// ������ 1. ������� ������� PMSV1_0_INTERACTIVE_PROFILE
/// </remarks>
NTSTATUS AllocateInteractiveProfile(
	_In_ PLSA_CLIENT_REQUEST ClientRequest,
	_Out_bytecapcount_(ProfileBufferSize) PVOID *ProfileBuffer,
	_Out_ PULONG ProfileBufferSize,
	_In_ OEM_SAM_HANDLE pSamTokenHandler
);

/// <summary>
/// ����������� ��� ������� ����������  InitSamDatabase.
/// </summary>
VOID FreeSamDatabase(
	OEM_SAM_HANDLE SamTokenHandler
);

#endif // !SAM_USER_TOKEN_INFO_H