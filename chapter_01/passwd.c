#include <stdio.h>
#include <pwd.h>

int main(void) {
	struct passwd *pwd;

	setpwent();
	while((pwd = getpwent()) != NULL)
		printf("uid=%d gid=%d name=%s\n",
			pwd->pw_uid, pwd->pw_gid, pwd->pw_name);
	endpwent();

	return 0;
}
