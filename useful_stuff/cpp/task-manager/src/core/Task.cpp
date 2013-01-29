#include "Task.hpp"

#include "FileUtilities.hpp"

Task::Task( ){

}

Task::Task( const string& tfilename ){

    /// Open the filename
    read( tfilename );

}


void Task::read( const string& filename ){

    bool note_start = false;

    /// Set the filename
    task_filename = filename;
    
    /// Open the file
    ifstream fin;
    fin.open( filename.c_str());
    
    string line;
    getline( fin, line );

    while( !fin.eof() ){
        
        if( note_start == true ){
            notes.push_back(line);
        }
        // check line
        else if( line.find("Name:") != string::npos ){
            name = line.substr(5);
        }
        else if( line.find("Groups:") != string::npos ){
            vector<string> tgroups = string_split(string_trim(line.substr(7)), ",");
            for( size_t i=0; i<tgroups.size(); i++ ){
                if( tgroups[i].size() > 0 )
                    groups.push_back( tgroups[i] );
            }

        }
        else if( line.find("Notes:") != string::npos ){
            note_start = true;
        }
    
        getline( fin, line );
    }


    fin.close();

}

ostream& operator << ( ostream& ostr, const Task& task ){

    ostr << "Name: " << task.name << endl;
    ostr << "Groups: ";
    if( task.groups.size() > 0 ){
        ostr << task.groups[0];
        for( size_t i=1; i<task.groups.size(); i++ )
            ostr << "," << task.groups[i];
    }
    ostr << endl;
    ostr << "Notes:" << endl;
    for( size_t i=0; i<task.notes.size(); i++ )
        ostr << task.notes[i] << endl;

    return ostr;
}


void new_task( deque<string> args, const string& task_directory ){
    

    // create an empty task
    Task newTask;

    // load the entries
    while( (int)args.size() > 0 ){
        if( args[0] == "-name" ){

            if( args.size() < 1 )
                throw string("Error: no filename given after -name");
            else{
                newTask.name = args[1];
                args.pop_front();
            }
            args.pop_front();
        } else if( args[0] == "-groups" ){

            if( args.size() < 1 )
                throw string("Error: no groups given after -groups");
            else{
                newTask.groups.push_back(args[1]);
                args.pop_front();
            }
            args.pop_front();
        } else if( args[0] == "-notes" ){
            args.pop_front();

            if( args.size() < 1 )
                throw string("Error: no filename given after -name");
            else{
                while( args.size() > 0 ){
                    newTask.notes.push_back(args[0]);
                    args.pop_front();
                }
            }
        }
    }

    // generate a filename
    newTask.task_filename = task_directory + string("/TASK_") + num2str(time(NULL)) + string(".task");
    
    // write to file
    ofstream fout;
    fout.open( newTask.task_filename.c_str());

    fout << newTask << endl;
    fout.close();

    
}


