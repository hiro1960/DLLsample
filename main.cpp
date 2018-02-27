// sqlite3.dllをVC++から使う
//
#include <stdio.h>
#include <windows.h>
#include "sqlite3.h"

// sqlite3.dll内関数ポインタ型定義
typedef int (__cdecl * pOpen)(char *, sqlite3 **);
typedef int (__cdecl * pExec)(sqlite3 *, const char *, sqlite3_callback, void *, char **);
typedef int (__cdecl * pGetTable)(sqlite3 *, const char *, char ***, int *, int *, char **);
typedef int (__cdecl * pFreeTable)(char **);
typedef int (__cdecl * pClose)(sqlite3 *);

int main() {

	HINSTANCE hDll;

	// 関数ポインタ変数
	pOpen sqlite3_open;
	pExec sqlite3_exec;
	pGetTable sqlite3_get_table;
	pFreeTable sqlite3_free_table;
	pClose sqlite3_close;

	// sqlite3.dllをロード
	hDll = LoadLibrary(TEXT("sqlite3"));  // ここ注意、文字列をLPCSTR型（const char*)に変更するためのTEXT()マクロ　古いVSだと、_T()マクロとなっている

	if (hDll == NULL) {
		return 0;
	}

	// sqlite3関数のアドレスを取得
	sqlite3_open = (pOpen)GetProcAddress(hDll, "sqlite3_open");
	sqlite3_exec = (pExec)GetProcAddress(hDll, "sqlite3_exec");
	sqlite3_get_table = (pGetTable)GetProcAddress(hDll, "sqlite3_get_table");
	sqlite3_free_table = (pFreeTable)GetProcAddress(hDll, "sqlite3_free_table");
	sqlite3_close = (pClose)GetProcAddress(hDll, "sqlite3_close");

	sqlite3 *db;
	char *err;
	char **result;
	int row, col;

	// データベースファイルを作成
	sqlite3_open("test.db", &db);

	// テーブル作成
	sqlite3_exec(db, "create table test(num integer,name string);", NULL, NULL, &err);

	// データを格納
	sqlite3_exec(db, "insert into test values(1,'test1');", NULL, NULL, &err);

	// データベースファイルを閉じる
	sqlite3_close(db);

	// データベースファイルを開く
	sqlite3_open("test.db", &db);

	// テーブルからデータを取得
	sqlite3_get_table(db, "select * from test;", &result, &row, &col, &err);

	// 取得したデータを表示
	printf("%s-%s\n", result[2], result[3]);

	// データ領域を解放
	sqlite3_free_table(result);

	// データベースファイルを閉じる
	sqlite3_close(db);

	// sqlite3.dll解放
	FreeLibrary(hDll);

	return 0;

}

