void removeBad(list<Restaurant*>& li) {
    for (auto it = li.begin(); it != li.end();) {
        if ((*it)->stars() <= 2) {
            delete *it;
            it = li.erase(it);
        } else {
            it++;
        }
    }
}