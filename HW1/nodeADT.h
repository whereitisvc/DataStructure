typedef struct node
{
        void* datap;
 struct node* link;           
}NODE;

NODE* creatNode( void* itemp )
{
      NODE* nodep;
      nodep = (NODE*)malloc( sizeof(NODE) );
      nodep->datap = itemp;
      nodep->link = NULL;
      return nodep;
}
