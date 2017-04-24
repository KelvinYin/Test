/***********************************************************************
 simple1.cpp - Example showing the simplest way to get data from a MySQL
	table with MySQL++.
***********************************************************************/

#include <mysql++.h>
#include <iostream>
#include <iomanip>

using namespace std;

int
main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
	// Get database access parameters from command line
	// mysqlpp::examples::CommandLine cmdline(argc, argv);
	// if (!cmdline) { return 1; }

	// Connect to the sample database.
	mysqlpp::Connection conn(false);
    // !Notice!: this option is a must
    conn.set_option(new mysqlpp::SetCharsetNameOption("utf8"));
	//if (conn.connect(mysqlpp::examples::db_name, cmdline.server(),
	//		cmdline.user(), cmdline.pass())) 
	if (conn.connect("zpsim", "localhost", "root", "123456"))
    {
		// Retrieve a subset of the sample stock table set up by resetdb
		// and display it.
		mysqlpp::Query query = conn.query("call sp_zpquery_product()");
		if (mysqlpp::StoreQueryResult res = query.store()) {
			cout << "We have:" << endl;
			mysqlpp::StoreQueryResult::const_iterator it;

            size_t nrows = res.num_rows();
            size_t nfields = res.num_fields();
            cout << "Affected rows  : " << nrows << endl;
            cout << "Affected fields: " << nfields << endl;
            cout << endl;

            for (size_t loop = 0; loop < nrows; ++ loop)
            {
                // for (size_t i = 0; i < res.field_names()->size(); i++) 
                for (size_t i = 0; i < nfields; i++) 
                {
                    cout << res.field_name(int(i)).c_str() << " ";
                    cout << res[loop][i] << endl;;
                }
            }
            cout << endl;;
  
            cout.setf(ios::left);
            for (size_t i = 0; i < nfields; i++) 
            {
                cout << setw(12) << res.field_name(int(i)).c_str() << " ";
            }
            cout << endl;
			for (it = res.begin(); it != res.end(); ++it) 
            {
				mysqlpp::Row row = *it;
				mysqlpp::Row::const_iterator rowIter = row.begin();
                for(;rowIter != row.end(); ++rowIter)
                {
                    cout << setw(12) << *rowIter<< " ";
                }
                cout << endl;
			}
		}
		else {
			cerr << "Failed to get item list: " << query.error() << endl;
			return 1;
		}

		return 0;
	}
	else {
		cerr << "DB connection failed: " << conn.error() << endl;
		return 1;
	}
}
