#ifndef WRITER_FACTORY_H

#pragma once

#include "defines.h"
#include <stdio.h>
#include <time.h>
#include "writer.h"

/// ��������� ������������!
/// ����������� ��������� <c> #include "logger.h>" </c>

/// ������� ��������
HRESULT BuildWriter(
	LOG_WRITER_TYPE type,
	PLOG_WRITER_METHODS * writer
);

/// ��������� ��� ������� ���������� ��������
VOID FreeWriter(
	VOID
);

#pragma region FILE LOG WRITER
/// <summary> �������������� ���� � ����� � �����.</summary>
HRESULT FileLogWriterInit(
	_In_ LPWSTR wsResourceName,
	_In_ LPCWSTR flags
);

/// <summary> ���������� ������ �� ����</summary>
HRESULT FileLogWriterFlash(
	_In_bytecount_(ulBufferToLogSize) LPBYTE pbBufferToLog,
	_In_ ULONG ulBufferToLogSize
);

/// <summary> ������� ���������� ������� </summary>
VOID FileLogWriterClose(
	VOID
);
#pragma endregion

#pragma region CONSOLE LOG WRITER
/// TODO
#pragma endregion

#pragma region SYSLOG LOG WRITER
/// TODO
#pragma endregion

#endif // !WRITER_FACTORY_H