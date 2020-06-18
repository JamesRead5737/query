#include <stdio.h>

int main (void)
{
	char *input;

	printf("Content-Type:text/html;charset=utf8\n");
	printf("<html>\n");
	printf("<head>\n");
	printf("<title>WoT ToT</title>\n");
	printf("</head>\n");
	printf("<body>\n");
	printf("<form action=\"http://www.wottot.com/cgi-bin/query\">i\n");
	printf("<div><input name=\"n\" size=100\%></div>\n");
	printf("<div><input type=\"submit\" value=\"Search\"></div>\n");
	printf("</form>\n");
	printf("</body>\n");
	printf("</html>\n");
}
