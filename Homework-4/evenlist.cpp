void removeEven(list<int>& li) {
    for (auto it = li.begin(); it != li.end();) {
        if (*it % 2 == 0) {
            it = li.erase(it);
        } else {
            it++;
        }
    }
}