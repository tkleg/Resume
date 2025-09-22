#define ORDER 5
typedef Album keyType;
typedef int IndexArray[ORDER];
typedef keyType ValueArray[ORDER-1];
struct BTNode
{
int currSize;
ValueArray contents;
IndexArray child;
};

class BTree{
    public:
        fstream initializeBTree( char* tFileName );
        BTNode createBTNode();
        BTree( char* treeFileName );
        fstream treeFile;
        BTNode root;
        char* treeFileName;
        int height;

        void printTree();
        BTNode getNode( int recAddr );
        void printNode( int recAddr );
        void insertAlbum( Album album, vector<int> & recAddrs, int recAddr, bool kickedUp );
        void insertAlbums( char* albumFileName );
        void pointToRoot();
        int rootAddr();
        void split( vector<int> & recAddrs, int recAddr, BTNode node, Album album, int index );
        void resetRoot( int location );
        void reassignChildren( int recAddr, int newChildAddr );
        //void reassignCurChildren( int recAddr );
        void putChildInPlace( BTNode & parent, int childAddr );
        void clearChildren( int recAddr );
        void parentSplit( int parentLocation, BTNode parent, int siblingLocation, BTNode sibling, vector<int> & recAddrs, Album album );
        //struct BTNodeComp;
    
    private:
        void printTree( int recAddr );
        void splitUp( Album album, vector<int> recAddrs, BTNode parent, BTNode node, BTNode sibling, int parentAddr, int nodeAddr, int sibAddr );
};