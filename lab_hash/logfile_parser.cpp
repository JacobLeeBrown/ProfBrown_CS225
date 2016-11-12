/**
 * @file logfile_parser.cpp
 * Implementation of the LogfileParser class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */

#include "logfile_parser.h"
#include <iostream>

using std::string;
using std::vector;
using std::ifstream;
using std::istringstream;

/**
 * Constructs a LogLine from a string (actual physical line in the
 * logfile).
 *
 * @param line The line in the file to extract info from.
 */
LogfileParser::LogLine::LogLine(const string& line)
{
    istringstream iss(line);
    iss >> customer;
    customer = customer.substr(1, customer.length() - 3);
    iss >> url;
    string dte = "";
    string dline;
    do {
        iss >> dline;
        dte += dline;
    } while (iss);

    date = time(NULL);
    tm* tme = localtime(&date);
    strptime(dte.c_str(), "%c", tme);
    // force correct DST
    tme->tm_isdst = 1;
    date = mktime(tme);
}

/**
 * Constructs a new LogfileParser from the name of a log file.
 *
 * @param fname The name of the log file to open.
 */
LogfileParser::LogfileParser(const string& fname) : whenVisitedTable(256)
{
	/* ~~~ I don't know why this table is instantiated, nor how it could be useful since it is local ~~~ */
	// SCHashTable<string, bool> pageVisitedTable(256);
    ifstream infile(fname.c_str());
    string line;
    while (infile.good()) {
        getline(infile, line);

        // if the line length is 0, move on to the next loop iteration
        if (line.length() == 0)
            continue;

        // otherwise parse the line and update the hash tables and vector
        LogLine ll(line);

        // Unique key for both the customer and the url he/she visted
        string name_page = ll.customer + " " + ll.url;

        // Set the respective entry in the member variable hashtable to the time 
        whenVisitedTable[name_page] = ll.date;

        /* ~~~ Would normally make helper function - Checks if uniqueURLs contains the URL, then inserts if needed ~~~ */
        bool contains = false;
        for(size_t i = 0; i < uniqueURLs.size(); i++)
        {
            if(uniqueURLs[i] == ll.url)
            {
                contains = true;
                break;
            }
        }
        if(!contains)
        {
            uniqueURLs.push_back(ll.url);
        }
        /* ~~~ End of helper function ~~~ */
    }
    infile.close();
}

/**
 * Determines if a given customer has ever visited the given url.
 *
 * @param customer The customer name.
 * @param url The url.
 * @return A boolean value indicating whether the customer visited the url.
 */
bool LogfileParser::hasVisited(const string& customer, const string& url) const
{
	// Reconstruct the unique key for a given customer and URL
	string name_page = customer + " " + url;
	// If find returns the default value type, the key was not found
	if(whenVisitedTable.find(name_page) == time_t()) return false;
	return true;
}

/**
 * Determines *when* a customer last visited a given url. If the customer
 * has not visited the given url, the output of this function should be the
 * default time_t.
 *
 * @param customer The customer name.
 * @param url The url.
 * @return A time_t representing when the customer last visited the given
 *  url.
 */
time_t LogfileParser::dateVisited(const string& customer,
                                  const string& url) const
{
	// Reconstruct the unique key for a given customer and URL
	string name_page = customer + " " + url;
	// Will return the time if it exists, or the default time_t if not
    return whenVisitedTable.find(name_page);
}

/**
 * Gets all of the unique urls that have been visited.
 *
 * @return A vector of urls that were visited in the logfile. Note
 *  that **there should be no duplicates in this vector**.
 */
vector<string> LogfileParser::uniquePages() const
{
    return uniqueURLs;
}
