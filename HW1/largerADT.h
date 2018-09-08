void* larger( void* p1 ,void* p2 ,int (*pfunt) (void*,void*) )
{
      if( (*pfunt)(p1,p2) > 0 )
          return p1;
      else if( (*pfunt)(p1,p2) < 0 )
          return p2;
      else
          return NULL;
}
