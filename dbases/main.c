#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <sqlite3.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

sqlite3 *db;

int fd_query;
int query_size;
char *query;
char *query_end;

const char *db_filename = "schema.sqlite3";
const char *query_filename = "queries.txt";

void init_table()
{
	if (sqlite3_open(db_filename, &db)) {
		fprintf(stderr, "Can't open database.\nError: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}

	fd_query = open(query_filename, O_RDONLY);
	if (fd_query < 0) {
		fprintf(stderr, "Can't open file for query: %s\nError: %s\n", query_filename, sqlite3_errmsg(db));
		exit(1);
	}

	struct stat buf;
	stat(query_filename, &buf);
	query_size = buf.st_size;
	fprintf(stderr, "size: %d\n", query_size);

	query = (char*) mmap(NULL, query_size, PROT_READ, 
						 MAP_SHARED, fd_query, 0);

	if (query == MAP_FAILED) {
		fprintf(stderr, "Can't mmap file for query: %s\n", query_filename);
		exit(1);
	} else {
		query_end = query + query_size;
		fprintf(stderr, "query has MMAPed: %s\n", query);
	}

}

#define LINE 256

void main_loop()
{
	static char line[LINE];
	static char command[LINE];
	static char instruction[LINE];
	static char table[LINE];
	static char *instruction_end;
	while (fgets(line, LINE, stdin) != NULL) {
		// читаем команду

		printf("1-day-till-deadline> ");

		char *pch = strtok(line, " \t\r\n");
		if (pch != NULL) {
			strcpy(command, pch);
		} else {
			printf("No command found!");
			continue;
		}

		if (strcmp(command, "add") == 0 || strcmp(command, "delete") == 0) {
			pch = strtok(NULL, " \t\r\n");
			if (pch != NULL) {
				strcpy(table, pch);
			} else {
				printf("No table found!");
			}

			pch = strtok(NULL, "");
			if (pch != NULL) {
				strcpy(instruction, pch);
				instruction_end = (char*) instruction + strlen(instruction);
			} else {
				printf("No instruction found!");
			}

			sqlite3_stmt *stmt;
			while (instruction < instruction_end) {
				printf("instruction: %x, instruction_end: %x", instruction, instruction_end);
				int rc = sqlite3_prepare_v2(db, instruction, instruction_end - instruction, 
						&stmt, &instruction);
				if (rc) {
					fprintf(stderr, "Can't prepare this instruction.\nError: %s", sqlite3_errmsg(db));
					continue;
				}

				while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {}

				if (rc != SQLITE_DONE) {
					printf("rc: %d\n", rc);
					fprintf(stderr, "Can't do step() on instruction .\nError: %s", sqlite3_errmsg(db));
					continue;
				} else {
					fprintf(stderr, "Everything is OK in step()");
				}

				rc = sqlite3_finalize(stmt);
				if (rc != SQLITE_OK) {
					fprintf(stderr, "Can't do finalize() on instruction.\nError: %s", sqlite3_errmsg(db));
					continue;
				}
			}
		}
	}
}

void create_table(int argc, char **argv)
{
	sqlite3_stmt *stmt;
	while (query < query_end) {
		printf("query: %x, query_end: %x", query, query_end);
		int rc = sqlite3_prepare_v2(db, query, query_end - query, &stmt, &query);
		if (rc) {
			fprintf(stderr, "\nCan't prepare statement.\nError: %s", sqlite3_errmsg(db));
			exit(1);
		}

		while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {}

		if (rc != SQLITE_DONE) {
			printf("rc: %d\n", rc);
			fprintf(stderr, "\nCan't do step() on statement.\nError: %s", sqlite3_errmsg(db));
			break;
			//exit(1);
		} else {
			fprintf(stderr, "\nEverything is OK in step()");
		}

		rc = sqlite3_finalize(stmt);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "\nCan't do finalize() on statement.\nError: %s", sqlite3_errmsg(db));
			exit(1);
		}
	}
}

void close_table()
{
	munmap(query, query_size);
	sqlite3_close(db);
}

int main(int argc, char **argv)
{
	init_table();

	create_table(argc, argv);

	main_loop();

	close_table();

	return 0;
}
