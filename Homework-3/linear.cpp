bool allFalse(const string a[], int n) {
    if (n <= 0) {
        return true;
    } else if (!somePredicate(a[0])) {
        return allFalse(a + 1, n - 1);
    } else {
        return false;
    }
}

int countFalse(const string a[], int n) {
    if (n <= 0) {
        return 0;
    } else if (!somePredicate(a[0])) {
        return 1 + countFalse(a + 1, n - 1);
    } else {
        return countFalse(a + 1, n - 1);
    }
}

int firstFalse(const string a[], int n) {
    if (n <= 0) {
        return -1;
    } else if (!somePredicate(a[0])) {
        return 0;
    } else {
        int result = firstFalse(a + 1, n - 1);

        if (result == -1) {
            return -1;
        }

        return 1 + result;
    }
}

int indexOfMax(const string a[], int n) {
	if (n <= 0) { 
        return -1; 
    } else if (n == 1) { 
        return 0; 
    } else {
        int mid = n / 2;
        int max1 = indexOfMax(a, mid);
	    int max2 = indexOfMax(a + mid, n - mid) + mid;

        if (a[max1] >= a[max2]) {
            return max1;
        } else {
            return max2;
        }
    }
}

bool has(const string a1[], int n1, const string a2[], int n2) {
    if (n2 <= 0) {
        return true;
    } else if (n1 <= 0) {
        return false;
    } else if (a1[0] == a2[0]) {
        return has(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
    } else {
        return has(a1 + 1, n1 - 1, a2, n2);
    }
}