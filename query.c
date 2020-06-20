#include <stdio.h>
#include <stdlib.h>
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
	strcpy(sql, "SELECT url, title FROM crawl.crawled ");
	input = getenv("QUERY_STRING");

	char *token;
	char *last;
	char *query;

	query = strtok(input, "=");
	query = strtok(NULL, "=");

	token = strtok(query, "+");
	if (token != NULL)
	{
		char escaped_token[(strlen(token)*2)+1];
		if (!mysql_real_escape_string(con, escaped_token, token, strlen(token)))
		{}
		sql = (char *) realloc(sql, strlen(sql) + strlen("INNER JOIN `` ON crawl.crawled.id = .id ") + strlen(escaped_token) + strlen(escaped_token) + 1);
		strcat(sql, "INNER JOIN `");
		strcat(sql, escaped_token);
		strcat(sql, "` ON crawl.crawled.id = ");
		strcat(sql, escaped_token);
		strcat(sql, ".id ");
		last = (char *) malloc(strlen(escaped_token) + 1);
		strcpy(last, escaped_token);
	}
	while (token != NULL)
	{
		token = strtok(NULL, "+");
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
	sql = (char *) realloc(sql, strlen(sql) + strlen("ORDER BY backlinks DESC") + 1);
	strcat(sql, "ORDER BY backlinks DESC");
	printf("Content-Type:text/html;charset=utf8\n\n");
	printf("<html>\n");
	printf("<head>\n");
	printf("<title>WoT ToT</title>\n");
	printf("<link rel=\"stylesheet\" href=\"http://www.wottot.com/styles.css\">\n");
	printf("</head>\n");
	printf("<body>\n");
	printf("<h1>WoT ToT</h1>\n");
	printf("<hr/>\n");
	printf("<form action=\"http://www.wottot.com/search/query\">\n");
	printf("<div><input type=\"text\" name=\"q\" placeholder=\"Enter keywords here\" autofocus></div>\n");
	printf("<div><input type=\"submit\" value=\"Search\"></div>\n");
	printf("</form>\n");
	printf("<div class=\"form\">\n");
	printf("<form class=\"paypal\" action=\"https://www.paypal.com/cgi-bin/webscr\" method=\"post\" target=\"_top\">\n");
	printf("<input type=\"hidden\" name=\"cmd\" value=\"_s-xclick\" />\n");
	printf("<input type=\"hidden\" name=\"hosted_button_id\" value=\"W9NAA722C66Z2\" />\n");
	printf("<input type=\"image\" src=\"https://www.paypalobjects.com/en_US/GB/i/btn/btn_donateCC_LG.gif\" border=\"0\" name=\"submit\" title=\"PayPal - The safer, easier way to pay online!\" alt=\"Donate with PayPal button\" />\n");
	printf("<img alt=\"\" border=\"0\" src=\"https://www.paypal.com/en_GB/i/scr/pixel.gif\" width=\"1\" height=\"1\" />\n");
	printf("</form>\n");
	printf("</div>\n");
	if (mysql_real_query(con, sql, (unsigned long)strlen(sql)))
	{}
	MYSQL_RES *result = mysql_use_result(con);
	if(result == NULL)
	{
		mysql_close(con);
	}
	else
	{
		MYSQL_ROW row;
		while ((row = mysql_fetch_row(result)))
		{
			printf("<a href=\"%s\">%s</a><br/>\n", row[0], row[0]);
			printf("%s<br/><br/>\n", row[1]);
		}
		mysql_free_result(result);
		mysql_close(con);
	}
	printf("</body>\n");
	printf("</html>\n");
	free(sql);
}
