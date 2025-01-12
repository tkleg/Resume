        #include "dsexceptions.h"
        #include <iostream>       // For NULL

        template <class Comparable>
        class BinarySearchTree;

        template <class Comparable>
        class BinaryNode
        {
            Comparable element;
            BinaryNode *left;
            BinaryNode *right;

            BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
              : element( theElement ), left( lt ), right( rt ) { }
            friend class BinarySearchTree<Comparable>;
        };

        template <class Comparable>
        class BinarySearchTree
        {
          public:
            explicit BinarySearchTree( const Comparable & notFound );
            BinarySearchTree( const BinarySearchTree & rhs );
            ~BinarySearchTree( );

            Comparable  findMin( ) const;
            Comparable  findMax( ) const;
            Comparable  find( const Comparable & x ) const;
            bool isEmpty( ) const;
            void printTree( ) const;

            //  Insert Prototype For postOrder Below
	          void postOrder() const;
            //  Insert Prototype For height Below	
		int height() const;
            //  Insert Prototype For numLeaves Below	
		int numLeaves() const;
            //  Insert Prototype For isBalanced Below	
		bool isBalanced() const;

            void makeEmpty( );
            void insert( const Comparable & x );
            void remove( const Comparable & x );

            const BinarySearchTree & operator=( const BinarySearchTree & rhs );

          private:
            BinaryNode<Comparable> *root;
            Comparable ITEM_NOT_FOUND;

            Comparable& elementAt( BinaryNode<Comparable> *t ) const;

            void insert( const Comparable & x, BinaryNode<Comparable> * & t ) const;
            void remove( const Comparable & x, BinaryNode<Comparable> * & t ) const;
            BinaryNode<Comparable> * findMin( BinaryNode<Comparable> *t ) const;
            BinaryNode<Comparable> * findMax( BinaryNode<Comparable> *t ) const;
            BinaryNode<Comparable> * find( const Comparable & x, BinaryNode<Comparable> *t ) const;
            void makeEmpty( BinaryNode<Comparable> * & t ) const;
            BinaryNode<Comparable> * clone( BinaryNode<Comparable> *t ) const;

            void printTree( BinaryNode<Comparable> *t ) const;

            // Insert Private postOrder Prototype Below 
	          void postOrder( BinaryNode<Comparable> * t ) const;

            // Insert Private height Prototype Below 
		int height( BinaryNode<Comparable> * t ) const;

            // Insert Private numLeaves Prototype Below 
		int numLeaves( BinaryNode<Comparable> * t ) const;

            // Insert Private isBalanced Prototype Below 
		bool isBalanced( BinaryNode<Comparable> * t ) const;
        };

        #include "bst.cpp"
