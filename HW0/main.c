#include <list.h>
#include <stdio.h>

int llTests(void) {
	struct linked_list * testll = ll_create();
	ll_add(testll, 5);
	if (ll_length(testll) != 1) {
		return 6;
	}
	if (!ll_contains(testll, 5)) {
		return 9;
	}
	if (ll_destroy(testll)) {
		return 12;
	}
	if (!ll_remove_first(testll)) {
		return 16;
	}
	if (ll_length(testll) != 0) {
		return 19;
	}
	if (ll_remove_first(testll)) {
		return 21;
	}
	printf("First half success!");
	ll_add(testll, 1);
	ll_add(testll, 23);
	ll_add(testll, 9);
	if (ll_length(testll) != 3) {
		return 27;
	}
	if (ll_contains(testll, 5)) {
		return 30;
	}
	if (!ll_contains(testll, 9)) {
		return 33;
	}
	if (ll_contains(testll, 23) != 2) {
		printf("%d", ll_contains(testll, 23));
		return 36;
	}
	ll_remove_first(testll);
	ll_remove_first(testll);
	ll_remove_first(testll);
	if (!ll_destroy(testll)) {
		return 42;
	}
	return 0;
}

int main(void) {
	printf("hello!");
	int res = llTests();
	if (res) {
		printf("problem on line %d", res);
		return 0;
	}
	printf("No problems!!");
	return 0;
}