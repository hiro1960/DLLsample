// sqlite3.dll��VC++����g��
//
#include <stdio.h>
#include <windows.h>
#include "sqlite3.h"

// sqlite3.dll���֐��|�C���^�^��`
typedef int (__cdecl * pOpen)(char *, sqlite3 **);
typedef int (__cdecl * pExec)(sqlite3 *, const char *, sqlite3_callback, void *, char **);
typedef int (__cdecl * pGetTable)(sqlite3 *, const char *, char ***, int *, int *, char **);
typedef int (__cdecl * pFreeTable)(char **);
typedef int (__cdecl * pClose)(sqlite3 *);

int main() {

	HINSTANCE hDll;

	// �֐��|�C���^�ϐ�
	pOpen sqlite3_open;
	pExec sqlite3_exec;
	pGetTable sqlite3_get_table;
	pFreeTable sqlite3_free_table;
	pClose sqlite3_close;

	// sqlite3.dll�����[�h
	hDll = LoadLibrary(TEXT("sqlite3"));  // �������ӁA�������LPCSTR�^�iconst char*)�ɕύX���邽�߂�TEXT()�}�N���@�Â�VS���ƁA_T()�}�N���ƂȂ��Ă���

	if (hDll == NULL) {
		return 0;
	}

	// sqlite3�֐��̃A�h���X���擾
	sqlite3_open = (pOpen)GetProcAddress(hDll, "sqlite3_open");
	sqlite3_exec = (pExec)GetProcAddress(hDll, "sqlite3_exec");
	sqlite3_get_table = (pGetTable)GetProcAddress(hDll, "sqlite3_get_table");
	sqlite3_free_table = (pFreeTable)GetProcAddress(hDll, "sqlite3_free_table");
	sqlite3_close = (pClose)GetProcAddress(hDll, "sqlite3_close");

	sqlite3 *db;
	char *err;
	char **result;
	int row, col;

	// �f�[�^�x�[�X�t�@�C�����쐬
	sqlite3_open("test.db", &db);

	// �e�[�u���쐬
	sqlite3_exec(db, "create table test(num integer,name string);", NULL, NULL, &err);

	// �f�[�^���i�[
	sqlite3_exec(db, "insert into test values(1,'test1');", NULL, NULL, &err);

	// �f�[�^�x�[�X�t�@�C�������
	sqlite3_close(db);

	// �f�[�^�x�[�X�t�@�C�����J��
	sqlite3_open("test.db", &db);

	// �e�[�u������f�[�^���擾
	sqlite3_get_table(db, "select * from test;", &result, &row, &col, &err);

	// �擾�����f�[�^��\��
	printf("%s-%s\n", result[2], result[3]);

	// �f�[�^�̈�����
	sqlite3_free_table(result);

	// �f�[�^�x�[�X�t�@�C�������
	sqlite3_close(db);

	// sqlite3.dll���
	FreeLibrary(hDll);

	return 0;

}

