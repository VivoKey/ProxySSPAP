// stdafx.h: ���������� ���� ��� ����������� ��������� ���������� ������,
// ��� ���������� ������ ��� ����������� �������, ������� ����� ������������, ��
// �� ����� ����������
//

#pragma once

#include "targetver.h"

// ��������� CppUnitTest
#include "CppUnitTest.h"
#define WIN32_LEAN_AND_MEAN             // ��������� ����� ������������ ���������� �� ���������� Windows
#define SECURITY_WIN32
#define UMDF_USING_NTSTATUS
// ����� ���������� Windows: ������� ����������� LSA Security API
#include <windows.h>
EXTERN_C_START
#include <ntstatus.h>
#include <sspi.h>
#include <NTSecAPI.h>
#include <NTSecPKG.h>

EXTERN_C_END

// TODO: ���������� ����� ������ �� �������������� ���������, ����������� ��� ���������
