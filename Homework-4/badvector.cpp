void removeBad(vector<Restaurant*>& v) {
    for (auto it = v.begin(); it != v.end();) {
        if ((*it)->stars() <= 2) {
            delete *it;
            it = v.erase(it);
        } else {
            it++;
        }
    }
}