
void listAll(const File* f, string path)  // two-parameter overload
{

    // file is empty
     if (f->files() == nullptr)
     {
         path += f->name();
         cout << "/" << path << endl;
         return;
     }

    
    cout << "/" << path << f-> name() << endl;


    for (vector<File*>::const_iterator it = f->files()->begin(); it != f->files()->end(); it++)
    {
        string temp;
        
        temp = path + f->name()+ "/";
            
        

        listAll(*it, temp);
    }
}

