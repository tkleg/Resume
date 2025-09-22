#include "includes.h"
#include "album.cpp"
#include "btree.h"

int main( int argc, char* argv[] ){
    BTree tree( argv[2] );
    tree.insertAlbums( argv[1] );
    tree.printTree();
    return 0;
}

/*struct BTree::BTNodeComp{
    bool operator()( int a, int b ) const {
      BTNode node1 = getNode(a), node2 = getNode(b);
      //the albums will be in sorted order in each node
      return node1.contents[0] < node2.contents[0];
    }
};*/

void BTree::insertAlbums( char* albumFileName ){
    fstream albumsIn( albumFileName, ios::in );
    Album aIn;
    while( albumsIn ){
        albumsIn >> aIn;
        if( aIn.getUPC() == "" )
            break;
        vector<int> recAddrs;
        cout << "Now inserting " << aIn;
        int rootAddrLocal = rootAddr();
        insertAlbum( aIn, recAddrs, rootAddrLocal, false );
        //printTree();
    }

}

BTree::BTree( char* tFileName ){

    treeFile = initializeBTree( tFileName );

    BTNode header = createBTNode();
    root = createBTNode();
    treeFile.seekg(0);
    treeFile.write( (const char *) &header, sizeof(BTNode) );
    int rootLocation = (int) treeFile.tellg();
    treeFile.seekg(0);
    header.child[0] = rootLocation;

    treeFile.write( (const char *) &header, sizeof(BTNode) );
    treeFile.write( (const char *) &root, sizeof(BTNode) );

    treeFile.seekg(0);

    treeFileName = tFileName;
    height = 0;

}

fstream BTree::initializeBTree( char* treeFileName ){    
    //make sure the file is an existing empty file
    // &> /dev/null redirects stderr and stdout to a trashbin. The ; lets the touch command run even if the rm fails
    string command = "rm " + string( treeFileName ) + " &> /dev/null ; touch " + string( treeFileName );
    system( command.c_str() );

    fstream bin( treeFileName, ios::in | ios::out | ios::binary );
    bin.seekg(0);

    return bin;
}

BTNode BTree::createBTNode(){
    BTNode start;
    start.currSize = 0;
    for( int x = 0; x < ORDER - 1; x++ ){
        start.contents[x] = Album();
        start.child[x] = -1;
    }
    start.child[ ORDER - 1 ] = -1;//needed since this runs one more time than the contents initializing
    return start;
}

void BTree::printTree(){
    cout << "-------- B-tree of height " << height << " --------" << endl;
    printTree( rootAddr() );
}

void BTree::printTree( int recAddr ){
    if( recAddr != -1 ){
        BTNode dummy = getNode(recAddr);
        printNode( recAddr );
        for( int x = 0; x <= dummy.currSize; x++ )
            printTree( dummy.child[x] );
    }
}

void BTree::printNode( int recAddr ){
    treeFile.seekg(recAddr);
    BTNode dummy;
    treeFile.read( (char *) &dummy, sizeof(BTNode) );
    cout << "    *** node of size " << dummy.currSize << " ***     " << endl;
    for( int x = 0; x < dummy.currSize; x++ )
        cout << dummy.contents[x];
}

BTNode BTree::getNode( int recAddr ){
    treeFile.seekg(recAddr);
    BTNode node;
    treeFile.read( (char *) &node, sizeof(BTNode) );
    return node;
}

void BTree::insertAlbum( Album album, vector<int> & recAddrs, int recAddr, bool kickedUp  ){
    recAddrs.push_back( recAddr );
    BTNode node;
    treeFile.seekg(recAddr);
    treeFile.read( (char *) &node, sizeof(BTNode) );    
    int index = 0;
    while( index < node.currSize ){
        if( album < node.contents[index] )
            break;
        index++;
    }

    //cout << album.getUPC() << " wants to insert at index " << index << endl;

    if( node.child[index] != -1 && !kickedUp){
      //      cout << " go to child for insert " << endl;
            insertAlbum( album, recAddrs, node.child[index], false );
    }else if( index <= node.currSize ){
        if( node.currSize == ORDER - 1 ){
        //    cout << "splitting" << endl;
            if( kickedUp )
                cout << "this should not print" << endl;
            split( recAddrs, recAddr, node, album, index );
        }else{
            for( int x = node.currSize; x > index; x-- )
                node.contents[x] = node.contents[x-1];
            node.contents[index] = album;
            node.currSize++;
            treeFile.seekg( recAddr );
            treeFile.write( (const char *) &node, sizeof(BTNode) );
        }
    }else
        cout << "this should not run" << endl;
    /*if( kickedUp && node.currSize == ORDER -1 ){
        reassignChildren( recAddr, -1 );
        insertAlbum( album, recAddrs, recAddrs[ recAddrs.size() - 2 ], true );
        reassignChildren( recAddr, -1 );
    }*/
    //reassignChildren( recAddr, -1 );
    recAddrs.pop_back();
}

void BTree::split( vector<int> & recAddrs, int recAddr, BTNode node, Album album, int index ){
    cout << "Now Splitting!" << endl;

    BTNode newParent = createBTNode(), 
        sibling = createBTNode();
    vector<Album> albums( node.contents, node.contents + ORDER - 1 );
    albums.insert( albums.begin() + index, album );

    //parent gets the median record
    newParent.contents[0] = Album(albums[2]);
    //clear the unneded albums from node to be split
    //clearChildren( recAddr );
    for( int x = 0; x < 2; x++ ){
        node.contents[x] = Album(albums[x]);
        //cout << albums[x].getUPC() << ", ";
    }
    //cout << " end node ";
    //cout << albums[2].getUPC() << ", end medium";
    for( int x = 2; x < ORDER - 1; x++ )
        node.contents[x] = Album();
    //reassignChildren( recAddr, -1 );//-1 represents now additional child
    //sibling gets the last 2 records
    for( int x = 3; x < ORDER; x++ ){
        sibling.contents[x-3] = Album(albums[x]);
        //cout << albums[x].getUPC() << ", ";
    }
    //cout << "end sibling" << endl;
    
    newParent.currSize = 1;
    node.currSize = 2;
    sibling.currSize = 2;

    newParent.child[0] = recAddr;
    treeFile.seekg(recAddr);
    treeFile.write( (const char *) &node, sizeof(BTNode) );

    treeFile.seekg(0, ios::end);
    int siblingLocation = (int) treeFile.tellg();
    newParent.child[1] = siblingLocation;
    treeFile.write( (const char *) &sibling, sizeof(BTNode) );
    
    if( recAddr == recAddrs[0] ){
        int newParentLocation = (int) treeFile.tellg();
        treeFile.write( (const char *) &newParent, sizeof(BTNode) );
        root = newParent;
        resetRoot( newParentLocation );
        height++;
        cout << "Now Adjusting Root!" << endl;
        return;
    }
    
    int parentLocation = recAddrs[ recAddrs.size() - 2 ];
    BTNode parent = getNode( parentLocation );
    if( parent.currSize != ORDER - 1 ){
        insertAlbum( albums[2], recAddrs, recAddrs[ recAddrs.size() - 2 ], true );
        reassignChildren( parentLocation, siblingLocation );//the parent node will reassign its children
    }else{
      //  cout << "parent split" << endl;
        recAddrs.pop_back();//allows referecning recAddrs[ recAddrs.size() -2 ] to be the parent's parent
        parentSplit( parentLocation, parent, siblingLocation, sibling, recAddrs, albums[2] );
    }
}

void BTree::parentSplit( int parentLocation, BTNode parent, int siblingLocation, BTNode sibling, vector<int> & recAddrs, Album album ){
    cout << "Now Splitting!" << endl;

    BTNode grandParent = createBTNode(), 
    uncle = createBTNode();

    //inserts sibling into the right location
    vector<int> children( parent.child, parent.child + ORDER );
    int indexToInsert = 0;
    while( !( sibling.contents[0] < getNode( children[indexToInsert] ).contents[0] ) ){
        indexToInsert++;
        if( indexToInsert == ORDER )
            break;
    }
    if( indexToInsert == ORDER )
        children.push_back( siblingLocation );
    else
        children.insert( children.begin() + indexToInsert, siblingLocation );

    for( int x = 0; x < ORDER; x++ )
        parent.child[x] = -1;
    for( int x = 0; x < 3; x++ ){
        parent.child[x] = children[x];
        uncle.child[x] = children[x+3];
    }

    /*cout << "printing new children iubuibviuiuv" << endl;
    cout << "index: " << index << ", sibindex: " << index << endl;
    for( int addr : children ){
        printNode( addr );
    }*/

    set<Album> albumSet( parent.contents, parent.contents + ORDER - 1 );
    albumSet.insert( album );
    vector<Album> albums;
    for( Album a : albumSet )
        albums.push_back( a );

    /*cout << endl << "parent " << endl;
    printNode( parentLocation );
    cout << endl;
    for( Album a : albums )
        cout << a;
    cout << "new children oinfrfn" << endl;*/

    for( int x = 0; x < 2; x++ ){
        parent.contents[x] = albums[x];
        uncle.contents[x] = albums[x+3];
    }
    grandParent.contents[0] = albums[2];

    parent.currSize = 2;
    uncle.currSize = 2;
    grandParent.currSize = 1;

    treeFile.seekg(parentLocation);
    treeFile.write( (const char *) &parent, sizeof(BTNode) );

    treeFile.seekg(0, ios::end);
    int uncleLocation = (int) treeFile.tellg();

    grandParent.child[0] = parentLocation;
    grandParent.child[1] = uncleLocation;

    treeFile.write( (const char *) &uncle, sizeof(BTNode) );

    int grandParentLocation = (int) treeFile.tellg();

    /*cout << "printing parent " << endl;
    printTree( parentLocation );
    cout << "printing uncle " << endl;
    printTree( uncleLocation );
    cout << "new tree printing" << endl;*/
    //printTree( grandParentLocation );

    if( parentLocation == recAddrs[0] ){//true is parent is the root 
        //int newRootLocation = grandParentLocation;
        treeFile.seekg(grandParentLocation);
        treeFile.write( (const char *) &grandParent, sizeof(BTNode) );
        root = grandParent;
        resetRoot( grandParentLocation );
        height++;
        cout << "Now Adjusting Root!" << endl;
        return;
        //printTree( rootAddr() );
    }

    int origGParentAddr = recAddrs[ recAddrs.size() - 2 ];
    BTNode origGParent = getNode( origGParentAddr );
    if( origGParent.currSize != ORDER - 1 ){
        insertAlbum( albums[2], recAddrs, recAddrs[ recAddrs.size() - 2 ], true );
        reassignChildren( origGParentAddr, uncleLocation );//the parent node will reassign its children
    }else{
        recAddrs.pop_back();
        parentSplit( origGParentAddr, origGParent, uncleLocation, uncle, recAddrs, albums[2] );
    }
    /*
    cout << "old grandparent printing" << endl;
    printNode( recAddrs[ recAddrs.size() - 2 ] );
    cout << "grandparent printed" << endl;*/

}

void BTree::splitUp( Album album, vector<int> recAddrs, BTNode parent, BTNode node, BTNode sibling, int parentAddr, int nodeAddr, int sibAddr ){
    BTNode oldParent = getNode( recAddrs[ recAddrs.size() - 2 ] );
    if( oldParent.currSize < ORDER - 1 ){
        int index = 0;
        while( index < oldParent.currSize ){
            if( album < node.contents[index] )
                break;
            index++;
        }

        for( int x = node.currSize; x > index; x-- )
                node.contents[x] = node.contents[x-1];
        node.contents[index] = album;
        node.currSize++;
        treeFile.seekg( recAddrs[ recAddrs.size() - 2 ] );
        treeFile.write( (const char *) &oldParent, sizeof(BTNode) );

        reassignChildren( recAddrs[ recAddrs.size() - 2 ], sibAddr );
    }


}

void BTree::clearChildren( int recAddr ){
    BTNode node = getNode( recAddr );
    for( int x = 0; x < ORDER - 1; x++ )
        node.child[x] = -1;
    treeFile.seekg( recAddr );
    treeFile.write( (const char *) &node, sizeof(BTNode) );
}

void BTree::putChildInPlace( BTNode & parent, int childAddr ){
    BTNode child = getNode( childAddr );
    int index = 0;
    bool setInLoop = false;
    while( index < parent.currSize ){
        if( child.contents[0] < parent.contents[index] ){
            parent.child[index] = childAddr;
            setInLoop = true;
            break;
        }
        index++;
    }
    if( !setInLoop )
        parent.child[ parent.currSize ] = childAddr;
}

void BTree::reassignChildren( int recAddr, int newChildAddr ){
    BTNode parent = getNode( recAddr );
    vector<int> children( parent.child, parent.child + ORDER );
    children.push_back( newChildAddr );
    clearChildren( recAddr );    
    for( int addr : children ){
        if( addr == -1 )
            continue;
        putChildInPlace( parent, addr );
    }
    treeFile.seekg( recAddr );
    treeFile.write( (const char *) &parent, sizeof(BTNode) );
}
/*
void BTree::reassignCurChildren( int recAddr ){
    BTNode parent = getNode( recAddr );
    int index = 0;
    for( int x = 0; x < ORDER; x++ ){
        if( parent.child[x] == -1 )
            continue;
        BTNode child = getNode( parent.child[x] );
        bool setInLoop = false;
        for( int y = 0; y < ORDER - 1; y++ )
            if( ! (child.contents[0] < parent.contents[y]) ){
                parent.child[y] = parent.child[x];
                setInLoop = true;
                if( y != x )
                    parent.child[x] = -1;
                break;
            }
        if( !setInLoop ){
            parent.child[ parent.currSize - 1 ] = parent.child[x];
            if( parent.currSize - 1 != x )
                parent.child[x] = -1;
        }
    }

    treeFile.seekg( recAddr );
    treeFile.write( (const char *) &parent, sizeof(BTNode) );

}
*/
void BTree::resetRoot( int location ){
    BTNode dummy;
    treeFile.seekg(0);
    treeFile.read( (char *) &dummy, sizeof(BTNode) );
    dummy.child[0] = location;
    treeFile.seekg(0);
    treeFile.write( (const char *) &dummy, sizeof(BTNode) );
}

void BTree::pointToRoot(){
    BTNode dummy;
    treeFile.seekg(0);
    treeFile.read( (char *) &dummy, sizeof(BTNode) );
    treeFile.seekg( dummy.child[0] );

}

int BTree::rootAddr(){
    BTNode dummy;
    treeFile.seekg(0);
    treeFile.read( (char *) &dummy, sizeof(BTNode) );
    return dummy.child[0];
}

/*
this version works for just a root
void BTree::insertAlbum( Album album ){
    BTNode dummy;
    treeFile.seekg(0);
    treeFile.read( (char *) &dummy, sizeof(BTNode) );
    BTNode node = getNode( dummy.child[0] );

    cout << "Now inserting " << album;

    int index = 0;
    bool shifted = false;
    while( index < node.currSize ){
        if( album < node.contents[index] ){
            //cout << "new upc: " << album.getUPC() << ", old upc: " 
            //<< node.contents[index].getUPC() << ", index: " << index << ", cursize: " << node.currSize << endl;
            for( int x = node.currSize; x > index; x-- )
                node.contents[x] = node.contents[x-1];
            node.contents[index] = album;
            shifted = true;
            break;
        }
        index++;
    }
    if( ! shifted )
        node.contents[index] = album;

    node.currSize++;

    root = node;

    pointToRoot();
    treeFile.write( (const char *) &node, sizeof(BTNode) );
}
*/