#include <stdio.h>
#include <grp.h>

int main(void) {
	struct group *grp;

	setgrent();
	while((grp = getgrent()) != NULL)
		printf("gid=%d name=%s\n",
			grp->gr_gid, grp->gr_name);
	endgrent();

	return 0;
}
