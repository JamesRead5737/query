#include <stdio.h>
#include <string.h>
#include <mysql.h>

int main (void)
{
	char *input;

	MYSQL *con = mysql_init(NULL);
	if (con == NULL)
	{
		exit(1);
	}

	if (mysql_real_connect(con, "localhost", "reader", "1q2w3e4r", "indexes", 0, NULL, 0) == NULL)
	{
		mysql_close(con);
		exit(1);
	}

	char *sql;
	sql = (char *) malloc(strlen("SELECT url, title FROM crawl.crawled " + 1));
	sql = "SELECT url, title FROM crawl.crawled ";
	input = getenv("QUERY_STRING");

	char *token;
	char *last;
	token = strtok(input, " ");
	if (token != NULL)
	{
		char escaped_token[(strlen(token)*2)+1];
		if (!mysql_real_escape_string(con, escaped_token, token, strlen(token)))
		{}
		sql = (char *) realloc(sql, 1000);
		/*
		sql = (char *) realloc(sql, strlen(sql) + strlen("INNER JOIN `` ON crawl.crawled.id = .id ") + strlen(escaped_token) + strlen(escaped_token) + 1);
		strcat(sql, "INNER JOIN `");
		strcat(sql, escaped_token);
		strcat(sql, "` ON crawl.crawled.id = ");
		strcat(sql, escaped_token);
		strcat(sql, ".id ");
		last = (char *) malloc(strlen(escaped_token) + 1);
		strcpy(last, escaped_token);
		*/
	}
	/*
	while (token != NULL)
	{
		token = strtok(NULL, " ");
		if (token != NULL)
		{
			char escaped_token[(strlen(token)*2)+1];
			if (!mysql_real_escape_string(con, escaped_token, token, strlen(token)))
			{}
			sql =(char *) realloc(sql, strlen(sql) + strlen("INNER JOIN `` ON .id = .id ") + strlen(escaped_token) + strlen(last) + strlen(escaped_token) + 1);
			strcat(sql, "INNER JOIN `");
			strcat(sql, escaped_token);
			strcat(sql, "` ON ");
			strcat(sql, last);
			strcat(sql, ".id = ");
			strcat(sql, escaped_token);
			strcat(sql, ".id ");
		}
	}
	*/
	printf("Content-Type:text/html;charset=utf8\n\n");
	printf("<html>\n");
	printf("<head>\n");
	printf("<title>WoT ToT</title>\n");
	printf("</head>\n");
	printf("<body>\n");
	printf("<h1>WoT ToT</h1>\n");
	printf("<hr/>\n");
	printf("<form action=\"http://www.wottot.com/cgi-bin/query\">\n");
	printf("<div><input name=\"q\" size=100%%></div>\n");
	printf("<div><input type=\"submit\" value=\"Search\"></div>\n");
	printf("</form>\n");
	printf("%s\n", sql);
	printf("</body>\n");
	printf("</html>\n");
}
