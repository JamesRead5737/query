#include <stdio.h>

int main (void)
{
	char *input;

	printf("Content-Type:text/html;charset=utf8\n\n");
	printf("<html>\n");
	printf("<head>\n");
	printf("<title>WoT ToT</title>\n");
	printf("</head>\n");
	printf("<body>\n");
	printf("<h1>WoT ToT</h1>\n");
	printf("<hr/>\n");
	printf("<form action=\"http://www.wottot.com/cgi-bin/query\">\n");
	printf("<div><input name=\"n\" size=100%%></div>\n");
	printf("<div><input type=\"submit\" value=\"Search\"></div>\n");
	printf("</form>\n");
	printf("</body>\n");
	printf("</html>\n");
}
