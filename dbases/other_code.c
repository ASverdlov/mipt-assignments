#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sqlite3.h>

char filename[] = "queries.txt";
char dataBseFilename[] = "films.sqlite3";

void handleSqliteError(sqlite3 *dataBase)
{
	printf("%s\n", sqlite3_errmsg(dataBase));
	sqlite3_close(dataBase);
	exit(1);
}

int main()
{
	int fd = 0;
	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		perror("Can't open a file");
		exit(1);
	}

	struct stat fileInfo;
	lstat(filename, &fileInfo);
	const char *data;
	if ((data = mmap(NULL, fileInfo.st_size, PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED)
	{
		perror("Can't mmap a file");
		exit(1);
	}

	sqlite3 *ikeaDataBase = NULL;
	if (sqlite3_open(dataBseFilename, &ikeaDataBase))
	{
		handleSqliteError(ikeaDataBase);
	}

	sqlite3_stmt *ppStmt;
	const char *endOfData = data + fileInfo.st_size;

	while (data < endOfData)
	{
		if (sqlite3_prepare_v2(ikeaDataBase, data, endOfData - data, &ppStmt, &data))
		{
			handleSqliteError(ikeaDataBase);
		}

		int res;
		while ((res = sqlite3_step(ppStmt)) == SQLITE_ROW) { }

		if (res != SQLITE_DONE)
		{
			handleSqliteError(ikeaDataBase);
		}

		if ((sqlite3_finalize(ppStmt)) != SQLITE_OK)
		{
			handleSqliteError(ikeaDataBase);
		}
	}

	sqlite3_close(ikeaDataBase);
	return 0;
}
