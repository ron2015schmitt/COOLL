#ifndef MATRICKS__TENSOR_H
#define MATRICKS__TENSOR_H 1

#include <stdarg.h>



namespace matricks {

 
 
  
  /****************************************************************************
   * Tensor -- mathematical vector class.
   ****************************************************************************   
   */

  template <class D> class Tensor :
    public TensorRW<D,Tensor<D> > {
  private:

    // *********************** OBJECT DATA ***********************************
    //
    // do NOT declare any other storage.
    // keep the instances lightweight
    
    std::valarray<D>* data_;
    Dimensions* dimensions_;

  public:     
    typedef D DataType;
    typedef typename FundamentalType<D>::Type PrimDataType;



    //**********************************************************************
    //************************** CONSTRUCTORS ******************************
    //**********************************************************************


    // --------------------- default CONSTRUCTOR ---------------------

    explicit Tensor<D>() 
    {
      dimensions_ = new Dimensions();
      data_ = new std::valarray<D>(dimensions_->datasize());
      constructorHelper();
    }

    // --------------------- constant=0 CONSTRUCTOR ---------------------

    explicit Tensor<D>(const Dimensions& dims) 
    {
      dimensions_ = new Dimensions(dims);
      data_ = new std::valarray<D>(dims.datasize());
      constructorHelper();
    }


    // --------------------- constant CONSTRUCTOR ---------------------

    explicit Tensor<D>(const Dimensions& dims, const D val) 
    {
      dimensions_ = new Dimensions(dims);
      data_ = new std::valarray<D>(val, dims.datasize());
      constructorHelper();
    }


    



    // --------------------- constructorHelper() --------------------
    
    void constructorHelper() {
    }







    //**********************************************************************
    //************************** DESTRUCTOR ******************************
    //**********************************************************************

    ~Tensor<D>() {
      delete  data_ ;

      //remove from directory
    }
  

    //**********************************************************************
    //************************** Size related  ******************************
    //**********************************************************************

    // --------------------- RESIZE ---------------------

    // These allow the user to resize a vector


    // *** this is used for recon by assignment ***

    TERW_Resize<D>  resize(void) { 
      return  TERW_Resize<D>(*this);
    }



    inline size_type size(void) const {
      return data_->size();
    }
    size_type depth(void) const {
      return 1;
    }
    size_type ndims(void) const {
      return dimensions_->ndims();
    }
    Dimensions dims(void) const {
      return *dimensions_;
    }
    bool isExpression(void) const {
      return false;
    }
    Tensors getEnum() const {
      return T_TENSOR;
    }

    VectorofPtrs getAddresses(void) const  {
      VectorofPtrs myaddr((void*)this);
      return myaddr;
    }

    inline size_type deepsize(void) const {
      return size();
    }



    Tensor& resize(const Dimensions& dims) {
      dimensions_ = new Dimensions(dims);
      data_->resize(dimensions_->datasize());
      return *this;
    }

    
    //**********************************************************************
    //*********************  Accesss to Internal valarray ******************
    //**********************************************************************

    // "read/write" to the wrapped valarray
    inline std::valarray<D>& getValArray()  {
      return *data_; 
    }
    inline Tensor<D>& setValArray(std::valarray<D>* valptr)  {
      delete  data_ ;
      const size_t N = valptr->size();
      data_ = valptr;
      return *this;
    }


    //**********************************************************************
    //************************** ACCESSS[] ***********************************
    //**********************************************************************


    // -------------------- ELEMENT ACCESS --------------------

    // "read/write" access signed index
    inline D& operator[](const index_type i)  {
      index_type index = i;
      if (i < 0) {
	index += size();
      }
      return (*data_)[index]; 
    }


    // "read only" access igned index
    inline const D operator[](const index_type i) const {
      return (const D)(*data_)[i]; 
    }

    
    //**********************************************************************
    //************************** INDEXING  *********************************
    //**********************************************************************
    
    index_type indexOf(const Indices& inds) const {
      return dimensions_->index(inds);
    }

    /* template<typename... Ts> index_type index(int i, const Ts... args){ */
    /* const int size = sizeof...(args); */
    /* int argarray[size] = {args...}; */
    /*   Indices& inds = *(new Indices(ndims())); */
    /*   const index_type M = this->ndims(); */
    /*   inds[0] = i;  */
    /*   for(index_type n = 1; n < M; n++) { */
    /* 	inds[n] = argarray[n];  */
    /*   } */
    /*   index_type k = this->index(inds); */
    /*   return k; */
    /* } */

    template <typename... U> typename std::enable_if<(std::is_same<U, int>::value && ...), index_type>::type index(const U... args) {
  
      const int size = sizeof...(args);
      int argarray[size] = {args...};
      Indices& inds = *(new Indices(ndims()));
      const index_type M = this->ndims();
      for(index_type n = 0; n < M; n++) {
    	inds[n] = argarray[n]; 
      }
      index_type k = this->indexOf(inds);
      return k;
    }

    
    index_type indexl(const std::initializer_list<size_type> mylist) const {
      // TODO: check size
      const index_type M = this->ndims();
      const size_type N =  mylist.size();
      index_type k = 0;
      index_type n = 0;
      typename std::initializer_list<size_type>::iterator it; 
      for (it = mylist.begin(); it != mylist.end(); ++it, n++)  { 
	size_type N = (*dimensions_)[n];
	index_type j = *it;
	k = N*k + j;
      }
      return k;
    }

   
    
    // indices - This is the inverse of the above function
    // TODO: test this code
    // TODO: bounds check on k
    
    inline Indices& indices(const index_type k) const {
      return dimensions_->indices(k);
    }



    //**********************************************************************
    //************************** ACCESS() ***********************************
    //**********************************************************************

    
    // ---------------- tensor(Indices)--------------
    D& operator()(const Indices& inds) {
      index_type k = this->index(inds);
      return (*this)[k];
    }
    const D operator()(const Indices& inds) const {
      index_type k = this->index(inds);
      return (*this)[k];
    }


    
    // ---------------- tensor(i,j,...)--------------

    template <typename... U> typename std::enable_if<(std::is_same<U, int>::value && ...), D&>::type operator()(const U... args) {
      index_type k = this->index(args...);
      return (*this)[k];
    }
    template <typename... U> typename std::enable_if<(std::is_same<U, int>::value && ...), const D>::type operator()(const U... args) const  {
    return (*this)(args...);
    }



    // ---------------- tensor({i,j,...})--------------
    D& operator()(const std::initializer_list<size_type> mylist) {
      index_type k = this->index(mylist);
      return (*this)[k];
    }
    const D operator()(const std::initializer_list<size_type> mylist) const {
      index_type k = this->index(mylist);
      return (*this)[k];
    }

    
    //**********************************************************************
    //************************** ASSIGNMENT **************************************
    //**********************************************************************

    // Any new assignment operators should also be addedc to TensorRW for consistency.
    // For this reason, in most cases, its preferred to overload the function vcast()
    // equals functions are included so that derived classes can call these functions


    // ----------------- tensor = d ----------------
    Tensor<D>& equals(const D d) { 
      for(index_type i=size(); i--;) 
	(*data_)[i]=d; 
      return *this;
    }
    Tensor<D>& operator=(const D d) { 
      return equals(d);
    }

    // ----------------- tensor = TensorR<D,A> ----------------
    Tensor<D>& equals(const Tensor<D>& x) {
      // TODO: issue warning
      resize(x.dims());
      for (index_type i = size(); i--;) {
	  (*data_)[i] = x[i];   // Inlined expression
      }
      return *this; 
    }
    Tensor<D>& operator=(const Tensor<D>& x) {  
      return equals(x);
    }

    // ----------------- tensor = TensorR<D,A> ----------------
    template <class A>  Tensor<D>& equals(const TensorR<D,A>& x) {
      // TODO: issue warning
      resize(x.dims());

      if (common(*this, x)){    
	Tensor<D> Ttemp(this->dims());
	for (index_type i = size(); i--;)
	  Ttemp[i] = x[i];   // Inlined expression
	for (index_type i = size(); i--;)
	  (*data_)[i] = Ttemp[i];
      } else {
	for (index_type i = size(); i--;)
	  (*data_)[i] = x[i];   // Inlined expression
      }
      return *this; 
    }
    template <class A>  Tensor<D>& operator=(const TensorR<D,A>& x) {  
      return equals(x);
    }


    //*********************************************************
    //                   1D assignment
    //********************************************************
    

    // ------------- tensor = array[] ----------------
    
    Tensor<D>& equals(const D array1[]) {
      for (index_type i = 0; i < size(); i++)  {
	(*this)[i] = array1[i];
      }
      return *this;
    }
    Tensor<D>& operator=(const D array1[]) {
      return equals(array1);
    }


    // --------------- matrix = initializer_list ------------------
    Tensor<D>& equals(const std::initializer_list<D>& mylist) {

      // TODO: bound scheck 
      size_type i = 0;
      typename std::initializer_list<D>::iterator it; 
      for (it = mylist.begin(); it != mylist.end(); ++it)  { 
	(*this)[i++] = *it;
      }

      return *this;
    }
    Tensor<D>& operator=(const std::initializer_list<D>& mylist) {
      return equals(mylist);
    }


    
    //**********************************************************************
    //************************** MATH **************************************
    //**********************************************************************

    
    //----------------- .roundzero(tol) ---------------------------
    // NOTE: in-place

    Tensor<D>&  roundzero(D tolerance = MatricksHelper<D>::tolerance) { 
      for(index_type i=size(); i--;) {
	(*data_)[i] = matricks::roundzero((*data_)[i], tolerance);
      }
      return *this;
    }

    //----------------- .conj() ---------------------------
    // NOTE: in-place

    template< typename T=D >
      typename std::enable_if<is_complex<T>{}, Tensor<T>& >::type conj() {
      for(index_type i=size(); i--;) {
	(*data_)[i] = std::conj((*data_)[i]);
      }
      return *this;
    }

    //**********************************************************************
    //************************** Text and debugging ************************
    //**********************************************************************

    inline std::string classname() const {
      D d;
      return "Tensor"+display::getBracketedTypeName(d);
    }


#if MATRICKS_DEBUG>=1
    std::string expression(void) const {
      return "";
    }
#endif


    std::ostream& send(std::ostream &stream, index_type& n, const Dimensions& dim) const {
      using namespace display;
      Style& style = FormatDataVector::style_for_punctuation;

      const int delta = this->ndims() - dim.ndims();
      if (delta == 0) {
	stream << std::endl;
      }
      std::string indent = "";
      for (index_type j = 0; j < delta; j++) {
	indent +=  "  ";
      }
      stream << indent << style.apply("{");
      Dimensions newdim(dim);
      newdim.erase(newdim.begin());
      
      if (dim.ndims() > 1 ) {
	stream << std::endl;
      } 

      for (index_type j = 0; j < dim[0]; j++) {
	if (dim.ndims() > 1 ) {
	  Dimensions newdim(dim);
	  newdim.erase(newdim.begin());
	  this->send(stream, n, newdim);
	  if (j < dim[0]-1)  {
	    stream << style.apply(",")<< std::endl;
	  } 
	} else {
	  dispval_strm(stream, (*this)[n++]);
	  if (j < dim[0]-1)  {
	    stream << style.apply(", ");
	  }
	}
      }
      if (dim.ndims() == 1) {
	stream << style.apply("}"); 
      } else if (dim.ndims() == this->ndims()) {
	stream << std::endl << indent << style.apply("}"); 
      } else {
	stream << std::endl << indent << style.apply("}"); 
      }
      return stream;
    }
    
    // stream << operator

    // TODO: implement format

    friend std::ostream& operator<<(std::ostream &stream, const Tensor<D>& t) {
      using namespace display;
      index_type n = 0;
      t.send(stream, n, t.dims());
      return stream;
    }


    //template <class D>	
    friend inline std::istream& operator>>(const std::string s,  Tensor<D>& x) {
      std::istringstream st(s);
      return (st >> x);
    }


    // stream >> operator
    // TODO: implement

    friend std::istream& operator>>(std::istream& stream,  Tensor<D>& x) {	
      return stream;
    }

    // --------------------- FRIENDS ---------------------

  

  };




};


#endif 

