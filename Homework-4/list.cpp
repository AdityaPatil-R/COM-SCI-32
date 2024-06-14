void listAll(const File* f, string path) {
    path += '/' + f->name();

    cout << path << endl;

    const vector<File*>* vp = f->files();
    
    if (vp != nullptr) {
        for (int k = 0; k < vp->size(); k++) {
            listAll((*vp)[k], path);
        }
    }
}