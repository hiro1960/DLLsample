## windowsにおけるDLLの利用例

sqlite3を題材に、dllのロードからAPIの定義、使用の単純な例を載せる。

ヘッダとして、sqlite3.hが必要。（sqliteのdllのパッケージに含まれています）
また、実行時にはsqlite3.dllをパスの通った場所、あるいは一番確実にはexeと同じ場所に置いておくこと。