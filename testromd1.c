#include <stdio.h>
#include <stdlib.h>
#include <sql.h>
#include <sqlext.h>


#define NAME_LEN 50
#define PHONE_LEN 20

void show_error() {
   printf("error\n");
}

int main() {
   SQLHENV henv;
   SQLHDBC hdbc;
   SQLHSTMT hstmt = 0;
   SQLRETURN retcode;
   SQLCHAR szmat_id[4], szmat_nom[50], szmat_uap[25], szmat_mat[10];
   SQLLEN cbmat_id = 0, cbmat_nom = 0, cbmat_uap = 0, cbmat_mat = 0;

   // Allocate environment handle
   retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);

   // Set the ODBC version environment attribute
   if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
      retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER*)SQL_OV_ODBC3, 0);

      // Allocate connection handle
      if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
         retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);

         // Set login timeout to 5 seconds
         if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
            SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);

            // Connect to data source
            retcode = SQLConnect(hdbc, (SQLCHAR*) "poleindus", 9, (SQLCHAR*) "poleindus", 9, (SQLCHAR*) "poleindus", 9);

            // Allocate statement handle
            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
               retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

               retcode = SQLExecDirect (hstmt, (SQLCHAR *) "SELECT * FROM poleindus.dbo.esd_mat", SQL_NTS);
               if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {

                  // Bind columns 1, 2, 3, and 4
                  retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, szmat_id,   4,  &cbmat_id);
                  retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, szmat_nom, 50, &cbmat_nom);
                  retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, szmat_uap, 25, &cbmat_uap);
				  retcode = SQLBindCol(hstmt, 4, SQL_C_CHAR, szmat_mat, 10, &cbmat_mat);

                  // Fetch and print each row of data. On an error, display a message and exit.
                  for (int i=0 ; i<2000 ; i++) {
                     retcode = SQLFetch(hstmt);
                     if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
                        show_error();
                     if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
                        printf( "%d: %s %s %s %s \n", i + 1, szmat_id, szmat_nom, szmat_uap, szmat_mat);
                     else
                        break;
                  }
               }

               // Process data
               if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
                  SQLCancel(hstmt);
                  SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
               }

               SQLDisconnect(hdbc);
            }

            SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
         }
      }
      SQLFreeHandle(SQL_HANDLE_ENV, henv);
   }
}
