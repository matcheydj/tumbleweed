/* _______              __
/ ___/ /  ___  __ _  / /  ___
/ /__/ _ \/ _ \/  ' \/ _ \/ _ \
\___/_//_/\___/_/_/_/_.__/\___/
*/
//
// This software is copyright (C) by the Lawrence Berkeley
// National Laboratory.  Permission is granted to reproduce
// this software for non-commercial purposes provided that
// this notice is left intact.
// 
// It is acknowledged that the U.S. Government has rights to
// this software under Contract DE-AC03-765F00098 between
// the U.S.  Department of Energy and the University of
// California.
//
// This software is provided as a professional and academic
// contribution for joint exchange. Thus it is experimental,
// is provided ``as is'', with no warranties of any kind
// whatsoever, no support, no promise of updates, or printed
// documentation. By using this software, you acknowledge
// that the Lawrence Berkeley National Laboratory and
// Regents of the University of California shall have no
// liability with respect to the infringement of other
// copyrights by any part of this software.
//
//  ANAG, LBNL
#ifdef HDF5  // if you don't have HDF5, then this file is useless

#ifndef HDF5_H
#define HDF5_H

#include <iostream>
using std::cout;
using std::endl;
#ifdef MPI
#include <mpi.h>
#endif

#include "LevelData.H"
#include "HDF5Portable.H"
// hdf5 #defines inline.... duh!
#undef inline
#include <string>
#include <map>
#include "RealVect.H"

using std::map;

class HDF5Handle;

// HDF5.H
// ============

template <class T>
int writeLevel(HDF5Handle& a_handle,
	                const int& a_level,
	                const LevelData<T>& a_data,
	                const Real& a_dx,
	                const Real& a_dt,
	                const Real& a_time,
	                const Box& a_domain,
	                const int& a_refRatio,
	                const IntVect& outputGhost = IntVect::Zero);

template <class T>
int readLevel(HDF5Handle& a_handle,
	               const int& a_level,
	               LevelData<T>& a_data,
	               Real& a_dx,
	               Real& a_dt,
	               Real& a_time,
	               Box& a_domain,
	               int& a_refRatio,
	               const Interval& a_comps = Interval(),
	               const IntVect& ghost = IntVect::Zero,
	               bool setGhost = false);

// More basic HDF5 functions.  These can be used at a persons own
// discretion.  Refer to the User's Guide for a description of how these
// functions interact with the convenience functions writeLevel, etc.

int write(HDF5Handle& a_handle,
           const BoxLayout& a_layout);


template <class T>
int write(HDF5Handle& a_handle,
	           const BoxLayoutData<T>& a_data,
	           const std::string& a_name,
	           const IntVect& outputGhost = IntVect::Zero);


template <class T>
int write(HDF5Handle& a_handle,
           const LevelData<T>& a_data,
           const std::string& a_name,
           const IntVect& outputGhost = IntVect::Zero);


int read(HDF5Handle& a_handle,
          Vector<Box>& boxes);

int readBoxes(HDF5Handle& a_handle,
		Vector<Vector<Box> >& boxes);

int readFArrayBox(HDF5Handle& a_handle,
	                                   FArrayBox&  a_fab,
	                                   int a_level,
	                                   int a_boxNumber,
	                                   const Interval& a_components,
	                                   const std::string& a_dataName = "data");


template <class T>
int read(HDF5Handle& a_handle,
	          BoxLayoutData<T>& a_data,
	          const std::string& a_name,
	          const BoxLayout& a_layout,
              const Interval&  a_comps = Interval(),
	          bool redefineData = true);


template <class T>
int read(HDF5Handle& a_handle,
	          LevelData<T>& a_data,
	          const std::string& a_name,
	          const DisjointBoxLayout& a_layout,
              const Interval& a_comps = Interval(),
	          bool redefineData = true);


 class HDF5Handle
 {
	 public:
		
			   enum mode { CREATE, OPEN_RDONLY, OPEN_RDWR };
		
			
			
			   HDF5Handle();
		
			
			   HDF5Handle(const std::string& a_filename, mode a_mode);
		
			
			
			   int open(const std::string& a_filename, mode a_mode);
		
			
			   bool isOpen() const;
		
			
			   void close();
		
			
			
			   void setGroupToLevel(int a_level);
		
			
			   int setGroup(const std::string& groupAbsPath);
		
			
			   const std::string& getGroup() const;
		
			   const hid_t& fileID() const;
		   const hid_t& groupID() const;
		   static hid_t box_id;
		   static hid_t intvect_id;
		   static hid_t realvect_id;
		
			 private:
				
					   HDF5Handle(const HDF5Handle&);
				   HDF5Handle& operator=(const HDF5Handle&);
				
					   hid_t         m_fileID;
				   hid_t         m_currentGroupID;
				   bool          m_isOpen;
				   std::string   m_filename; // keep around for debugging
				   std::string   m_group;
				   int           m_level;
				
					   static hid_t  file_access;
				   static bool   initialized;
				   static void   initialize();
				
					 };


 class HDF5HeaderData
 {
	 public:
		
			
			   int writeToFile(HDF5Handle& file) const;
		
			
			   int readFromFile(HDF5Handle& file);
		
			   void clear();
		
			   map<std::string, Real>        m_real;
		
			   map<std::string, int>         m_int;
		
			   map<std::string, std::string> m_string;
		
			   map<std::string, IntVect>     m_intvect;
		
			   map<std::string, Box>         m_box;
		
			   map<std::string, RealVect>    m_realvect;
		
			   //users should not need these functions in general
			
			   int writeToLocation(hid_t loc_id) const;
		   int readFromLocation(hid_t loc_id);
		
			 private:
				   static herr_t attributeScan(hid_t loc_id, const char *name, void *opdata);
				 };

 extern "C" {
	 herr_t HDF5HeaderDataattributeScan(hid_t loc_id, const char *name, void *opdata);
	           }

 std::ostream& operator<<(std::ostream& os, const HDF5HeaderData& data);


 //=============================================================================
 //
 // end of declarations.
 //
 //=============================================================================

 //#include "HDF5Implem.H"
 /* _______              __
	     / ___/ /  ___  __ _  / /  ___
	    / /__/ _ \/ _ \/  ' \/ _ \/ _ \
	    \___/_//_/\___/_/_/_/_.__/\___/
	   */
	 //
	 // This software is copyright (C) by the Lawrence Berkeley
	 // National Laboratory.  Permission is granted to reproduce
	 // this software for non-commercial purposes provided that
	 // this notice is left intact.
	 // 
	 // It is acknowledged that the U.S. Government has rights to
	 // this software under Contract DE-AC03-765F00098 between
	 // the U.S.  Department of Energy and the University of
	 // California.
	 //
	 // This software is provided as a professional and academic
	 // contribution for joint exchange. Thus it is experimental,
	 // is provided ``as is'', with no warranties of any kind
	 // whatsoever, no support, no promise of updates, or printed
	 // documentation. By using this software, you acknowledge
	 // that the Lawrence Berkeley National Laboratory and
	 // Regents of the University of California shall have no
	 // liability with respect to the infringement of other
	 // copyrights by any part of this software.
	 //
	 //  ANAG, LBNL
	
	 #include "LoadBalance.H"
	 #include "LayoutIterator.H"
	 #include "Vector.H"
	 #include "memtrack.H"
	
	
	 // non-user code used in implementation of communication
	
	 struct OffsetBuffer
	 {
	   Vector<int> index;
	   Vector<Vector<int> > offsets;
	   void operator=(const OffsetBuffer& rhs);
	 };

 ostream& operator<<(ostream& os, const OffsetBuffer& ob);

 //OffsetBuffer specialization of linearSize
 template < >
 int linearSize(const OffsetBuffer& a_input);

 //OffsetBuffer specialization of linearIn
 template < >
 void linearIn(OffsetBuffer& a_outputT, const void* const a_inBuf);

 //OffsetBuffer specialization of linearOut
template < >
void linearOut(void* const a_outBuf, const OffsetBuffer& a_inputT);
template < > int linearSize(const Vector<OffsetBuffer>& a_input);
template < > void linearIn(Vector<OffsetBuffer>& a_outputT, const void* const inBuf);
template < > void linearOut(void* const a_outBuf, const Vector<OffsetBuffer>& a_inputT);
// First, template specializations for read/write for FArrayBox.
template <>
inline void dataTypes(Vector<hid_t>& a_types, const BaseFab<int>& dummy)
{
	   a_types.resize(1);
	   a_types[0] = H5T_NATIVE_INT;
	 }

 /* since many compilers choke on the proper template specialization syntax
	      I am forced to pass in a dummy specialization argument
	      */
	 template <>
	 inline void dataTypes(Vector<hid_t>& a_types, const FArrayBox& dummy)
	 {  a_types.resize(1); a_types[0] = H5T_NATIVE_REAL; }


 template <>
 inline void dataSize(const BaseFab<int>& item, Vector<int>& a_sizes,
	                      const Box& box, const Interval& comps)
	 {
	   a_sizes[0] = box.numPts() * comps.size();
	 }

 template <>
 inline void dataSize(const FArrayBox& item, Vector<int>& a_sizes,
	                      const Box& box, const Interval& comps)
	 {
	   a_sizes[0] = box.numPts() * comps.size();
	 }

 template <>
 inline const char* name(const FArrayBox& a_dummySpecializationArg)
 {
	   // Attempt to get rid of warnings on IBM...
		   //static const char* name = "FArrayBox";
		   const char* name = "FArrayBox";
	   return name;
	 }

 template <>
 inline const char* name(const BaseFab<int>& a_dummySpecializationArg)
 {
	   // Attempt to get rid of warnings on IBM...
		   //static const char* name = "BaseFab<int>";
		   const char* name = "BaseFab<int>";
	   return name;
	 }

 //
 // now, generic, non-binary portable version of template functions
 // for people who just want ot rely on linearIn/linearOut

 template <class T>
 inline void dataTypes(Vector<hid_t>& a_types, const T& dummy)
 {  a_types.resize(1); a_types[0] = H5T_NATIVE_CHAR; }

 template <class T>
 inline void dataSize(const T& item, Vector<int>& a_sizes,
	                      const Box& box, const Interval& comps)
	 {
	   a_sizes[0] = item.size(box, comps);
	 }


 template <class T>
 inline void write(const T& item, Vector<void*>& a_allocatedBuffers,
	                   const Box& box, const Interval& comps)
	 {
	   item.linearOut(a_allocatedBuffers[0], box, comps);
	 }

 template <class T>
 inline void read(T& item, Vector<void*>& a_allocatedBuffers,
	                  const Box& box, const Interval& comps)
	 {
	   item.linearIn(a_allocatedBuffers[0], box, comps);
	 }

 template <class T>
 inline const char* name(const T& a_dummySpecializationArg)
 {
	   static const char* name = "unknown";
	   return name;
	 }

 template <class T>
 void getOffsets(Vector<Vector<long long> >& offsets, const BoxLayoutData<T>& a_data,
	                 int types, const Interval& comps, const IntVect& outputGhost)
	 {
	
		
		   const BoxLayout& layout = a_data.boxLayout();
	   offsets.resize(types, Vector<long long>(layout.size() + 1));
	   //  offsets.resize(layout.size() + 1, Vector<long long>(types));
		   for (int t = 0; t<types; t++) offsets[t][0] = 0;
	   Vector<int> thisSize(types);
	   if (T::preAllocatable() == 0)
		   { // static preAllocatable
		     T dummy;
		     unsigned int index = 1;
		     for (LayoutIterator it(layout.layoutIterator()); it.ok(); ++it)
			       {
			         Box region = layout[it()];
			         region.grow(outputGhost);
			         dataSize(dummy, thisSize, region, comps);
			         for (unsigned int i = 0; i<thisSize.size(); ++i)
				           {
				             //offsets[index][i] = offsets[index-1][i] + thisSize[i];
					             offsets[i][index] = offsets[i][index - 1] + thisSize[i];
				           }
			         ++index;
			       }
		   }
	   else
		   { // symmetric and dynamic preallocatable need two pass I/O
		     OffsetBuffer buff;
		         int index = 0;
		     for (DataIterator dit(a_data.dataIterator()); dit.ok(); ++dit, ++index)
			       {
			         //int index = dit().intCode();
				         buff.index.push_back(index);
			         Box region = layout[dit()];
			         region.grow(outputGhost);
			         dataSize(a_data[dit()], thisSize, region, comps);
			         buff.offsets.push_back(thisSize);
			       }
		     Vector<OffsetBuffer> gathering(numProc());
		     gather(gathering, buff, uniqueProc(SerialTask::compute));
		     broadcast(gathering, uniqueProc(SerialTask::compute));
		     //  pout() << gathering<<endl;
			     for (int i = 0; i<numProc(); ++i)
			       {
			         OffsetBuffer& offbuf = gathering[i];
			         for (int num = 0; num<offbuf.index.size(); num++)
				           {
				             int index = offbuf.index[num];
				             for (unsigned int j = 0; j<types; ++j)
					               {
					                 //offsets[index+1][j] = offbuf.offsets[num][j];
						                 offsets[j][index + 1] = offbuf.offsets[num][j];
					               }
				           }
			       }
		     for (int i = 0; i<layout.size(); i++)
			       {
			         for (unsigned int j = 0; j<types; ++j)
				           {
				             //offsets[i+1][j] += offsets[i][j];
					             offsets[j][i + 1] += offsets[j][i];
				           }
			       }
		   }
	
		   // pout() << offsets<<endl;
		 }


 //==================================================================
 //
 // Now, linear IO routines for a BoxLayoutData of T
 //

 template <class T>
 int write(HDF5Handle& a_handle, const BoxLayoutData<T>& a_data,
	           const std::string& a_name, const IntVect& outputGhost)
	 {
	   int ret = 0;
	
		   Interval comps = a_data.interval(); // later, we can make comps an argument.....
	   T dummy; // used for preallocatable methods for dumb compilers.
	   Vector<hid_t> types;
	   dataTypes(types, dummy);
	
		   Vector<Vector<long long> > offsets;
	   Vector<long long> bufferCapacity(types.size(), 1);  // noel (was 0)
	   Vector<void*> buffers(types.size(), NULL);
	
		   getOffsets(offsets, a_data, types.size(), comps, outputGhost);
	
		   // create datasets collectively.
		   hsize_t flatdims[1];
	   char dataname[100];
	   Vector<hid_t> dataspace(types.size());
	   Vector<hid_t> dataset(types.size());
	
		
		
		   herr_t err;
	   hsize_t count[1];
	   hssize_t offset[1];
	
		   for (unsigned int i = 0; i<types.size(); ++i)
		     {
		       flatdims[0] = offsets[i][offsets[i].size() - 1];
		       sprintf(dataname, "%s:datatype=%i", a_name.c_str(), i);
		       dataspace[i] = H5Screate_simple(1, flatdims, NULL);
		       assert(dataspace[i] >= 0);
		       dataset[i] = H5Dcreate(a_handle.groupID(), dataname,
			                                     types[i],
			                                     dataspace[i], H5P_DEFAULT);
		       assert(dataset[i] >= 0);
		     }
	
		   hid_t offsetspace, offsetData;
	   for (unsigned int i = 0; i<types.size(); ++i)
		     {
		       flatdims[0] = offsets[i].size();
		       sprintf(dataname, "%s:offsets=%i", a_name.c_str(), i);
		       offsetspace = H5Screate_simple(1, flatdims, NULL);
		       assert(offsetspace >= 0);
		       offsetData = H5Dcreate(a_handle.groupID(), dataname,
			                                 H5T_NATIVE_LLONG, offsetspace, H5P_DEFAULT);
		       assert(offsetData >= 0);
		       if (procID() == 0)
			       {
			         hid_t memdataspace = H5Screate_simple(1, flatdims, NULL);
			         assert(memdataspace >= 0);
			         err = H5Dwrite(offsetData, H5T_NATIVE_LLONG, memdataspace, offsetspace,
				                        H5P_DEFAULT, &(offsets[i][0]));
			         assert(err >= 0);
			         H5Sclose(memdataspace);
			       }
		       H5Sclose(offsetspace);
		       H5Dclose(offsetData);
		     }
		   // write BoxLayoutData attributes into Dataset[0]
		   HDF5HeaderData info;
	   info.m_int["comps"] = comps.size();
	   info.m_string["objectType"] = name(dummy);
	   std::string group = a_handle.getGroup();
	   a_handle.setGroup(group + "/" + a_name + "_attributes");
	   info.writeToFile(a_handle);
	   a_handle.setGroup(group);
	
		   // collective operations finished, now perform parallel writes
		   // to specified hyperslabs.
		
		   Vector<size_t> type_size(types.size());
	   for (unsigned int i = 0; i<types.size(); ++i)
		     {
		       type_size[i] = H5Tget_size(types[i]);
		     }
	
		   Vector<int> thisSize(types.size());
	
		   // step 1, create buffer big enough to hold the biggest linearized T
		   // that I will have to output.
		   for (DataIterator it = a_data.dataIterator(); it.ok(); ++it)
		     {
		       unsigned int index = a_data.boxLayout().index(it());
		       for (unsigned int i = 0; i<types.size(); ++i)
			         {
			           long long size = (offsets[i][index + 1] - offsets[i][index])
				 * type_size[i];
			           assert(size > 0);
			           if (size > bufferCapacity[i]) // grow buffer if necessary.....
				             {
				               bufferCapacity[i] = size;
				             }
			         }
		     }
	   for (unsigned int i = 0; i<types.size(); ++i)
		     {
		       buffers[i] = malloc(bufferCapacity[i]);
		       if (buffers[i] == NULL) {
			         pout() << " i=" << i
				 << " types.size() = " << types.size()
				 << " bufferCapacity[i] = " << (int)bufferCapacity[i]
				 << endl;
			         MayDay::Error("memory error in buffer allocation write");
			
		}
		     }
	
		   // Step 2.  actually a) write each of my T objects into the
		   // buffer, then b) write that buffered data out to the
		   // write position in the data file using hdf5 hyperslab functions.
		   for (DataIterator it = a_data.dataIterator(); it.ok(); ++it)
		     {
		       const T& data = a_data[it()];
		       unsigned int index = a_data.boxLayout().index(it());
		       Box box = a_data.box(it());
		       box.grow(outputGhost);
		       write(data, buffers, box, comps); //write T to buffer
		       for (unsigned int i = 0; i<types.size(); ++i)
			         {
			           offset[0] = offsets[i][index];
			           count[0] = offsets[i][index + 1] - offset[0];
			           assert(count[0] > 0);
			           err = H5Sselect_hyperslab(dataspace[i], H5S_SELECT_SET,
				                                      offset, NULL,
				                                      count, NULL);
			           assert(err >= 0);
			           hid_t memdataspace = H5Screate_simple(1, count, NULL);
			           assert(memdataspace >= 0);
			           err = H5Dwrite(dataset[i], types[i], memdataspace, dataspace[i],
				                          H5P_DEFAULT, buffers[i]);
			           assert(err >= 0);
			           H5Sclose(memdataspace);
			           if (err < 0) { ret = err; goto cleanup; }
			         }
		     }
	
		   // OK, clean up data structures
		
		  cleanup:
	   for (unsigned int i = 0; i<types.size(); ++i)
		     {
		       free(buffers[i]);
		       H5Sclose(dataspace[i]);
		       H5Dclose(dataset[i]);
		     }
	   return ret;
	
		 }

 template <class T>
 int write(HDF5Handle& a_handle, const LevelData<T>& a_data,
	           const std::string& a_name, const IntVect& outputGhost)
	 {
	   HDF5HeaderData info;
	   info.m_intvect["ghost"] = a_data.ghostVect();
	   IntVect og(outputGhost);
	   og.min(a_data.ghostVect());
	   info.m_intvect["outputGhost"] = og;
	   std::string group = a_handle.getGroup();
	   a_handle.setGroup(group + "/" + a_name + "_attributes");
	   info.writeToFile(a_handle);
	   a_handle.setGroup(group);
	   return write(a_handle, (const BoxLayoutData<T>&)a_data, a_name, og);
	 }

 template <class T>
 int read(HDF5Handle& a_handle, LevelData<T>& a_data, const std::string& a_name,
	          const DisjointBoxLayout& a_layout, const Interval& a_comps, bool a_redefineData)
	 {
	   if (a_redefineData)
		     {
		       HDF5HeaderData info;
		       std::string group = a_handle.getGroup();
		       if (a_handle.setGroup(group + "/" + a_name + "_attributes"))
			         {
			           std::string message = "error opening " + a_handle.getGroup() + "/" + a_name;
			           MayDay::Warning(message.c_str());
			           return 1;
			         }
		       info.readFromFile(a_handle);
		       a_handle.setGroup(group);
		       int ncomp = info.m_int["comps"];
		       IntVect ghost = info.m_intvect["ghost"];
		           if (a_comps.end() > 0 && ncomp < a_comps.end())
			                 {
			                   MayDay::Error("attempt to read component interval that is not available");
			                 }
		           if (a_comps.size() == 0)
			                 a_data.define(a_layout, ncomp, ghost);
		           else
			                 a_data.define(a_layout, a_comps.size(), ghost);
		     }
	   return read(a_handle, (BoxLayoutData<T>&)a_data, a_name, a_layout, a_comps, false);
	
		 }
 template <class T>
 int read(HDF5Handle& a_handle, BoxLayoutData<T>& a_data, const std::string& a_name,
	          const BoxLayout& a_layout, const Interval& a_comps, bool a_redefineData)
	 {
	   int ret = 0; // return value;
	
		   herr_t err;
	
		   char dataname[100];
	   hsize_t count[1];
	   hssize_t offset[1];
	   Vector<Vector<long long> > offsets;
	
		   T dummy;
	   Vector<hid_t> types;
	   dataTypes(types, dummy);
	   Vector<hid_t> dataspace(types.size());
	   Vector<hid_t> dataset(types.size());
	   offsets.resize(types.size(), Vector<long long>(a_layout.size() + 1));
	
		   Vector<int> bufferCapacity(types.size(), 500);
	   Vector<void*> buffers(types.size(), NULL);
	
		   for (unsigned int i = 0; i<types.size(); ++i)
		     {
		       sprintf(dataname, "%s:datatype=%i", a_name.c_str(), i);
		       dataset[i] = H5Dopen(a_handle.groupID(), dataname);
		       if (dataset[i] < 0) { MayDay::Warning("dataset open failure"); return dataset[i]; }
		       dataspace[i] = H5Dget_space(dataset[i]);
		       if (dataspace[i] < 0) { MayDay::Warning("dataspace open failure"); return dataspace[i]; }
		     }
	
		   hid_t offsetspace, offsetData;
	   hsize_t flatdims[1];
	   for (unsigned int i = 0; i<types.size(); ++i)
		     {
		       flatdims[0] = offsets[i].size();
		       sprintf(dataname, "%s:offsets=%i", a_name.c_str(), i);
		       offsetspace = H5Screate_simple(1, flatdims, NULL);
		       assert(offsetspace >= 0);
		       offsetData = H5Dopen(a_handle.groupID(), dataname);
		       assert(offsetData >= 0);
		       hid_t memdataspace = H5Screate_simple(1, flatdims, NULL);
		       assert(memdataspace >= 0);
		       err = H5Dread(offsetData, H5T_NATIVE_LLONG, memdataspace, offsetspace,
			                      H5P_DEFAULT, &(offsets[i][0]));
		       assert(err >= 0);
		       H5Sclose(memdataspace);
		       H5Sclose(offsetspace);
		       H5Dclose(offsetData);
		     }
	
		   HDF5HeaderData info;
	   std::string group = a_handle.getGroup();
	   if (a_handle.setGroup(a_handle.getGroup() + "/" + a_name + "_attributes"))
		     {
		       std::string message = "error opening " + a_handle.getGroup() + "/" + a_name;
		       MayDay::Warning(message.c_str());
		       return 1;
		     }
	
		   info.readFromFile(a_handle);
	   a_handle.setGroup(group);
	   int ncomps = info.m_int["comps"];
	   IntVect outputGhost(IntVect::Zero); // backwards file compatible mode.
	   if (info.m_intvect.find("outputGhost") != info.m_intvect.end())
		     {
		       outputGhost = info.m_intvect["outputGhost"];
		     }
	   if (ncomps <= 0) {
		     MayDay::Warning("ncomps <= 0 in read");
		     return ncomps;
		
	}
	
		   if (a_redefineData) {
		         if (a_comps.size() != 0) {
			           a_data.define(a_layout, a_comps.size());
			
		}
		else {
			           a_data.define(a_layout, ncomps);
			
		}
		
	}
	
		   Interval comps(0, ncomps - 1);
	   if (a_comps.size() != 0)  comps = Interval(0, a_comps.size());
	
		   //  getOffsets(offsets, a_data, types.size(), comps);
		
		   Vector<size_t> type_size(types.size());
	   for (unsigned int i = 0; i<types.size(); ++i)
		     {
		       type_size[i] = H5Tget_size(types[i]);
		       buffers[i] = malloc(bufferCapacity[i]);
		       if (buffers[i] == NULL) {
			         pout() << " i= " << i
				 << " types.size()=" << types.size()
				 << " bufferCapacity[i] = " << (int)bufferCapacity[i]
				 << endl;
			         MayDay::Error("memory error in buffer allocation read");
			
		}
		     }
	
		   Vector<int> thisSize(types.size());
	   for (DataIterator it = a_data.dataIterator(); it.ok(); ++it)
		     {
		       T& data = a_data[it()];
		       unsigned int index = a_data.boxLayout().index(it());
		       Box box = a_data.box(it());
		
			       for (unsigned int i = 0; i<types.size(); ++i)
			         {
			                   if (a_comps.size() == 0) {
				                         offset[0] = offsets[i][index];
				                         count[0] = offsets[i][index + 1] - offset[0];
				
			}
			else {
				                         offset[0] = offsets[i][index] + box.numPts()*a_comps.begin();
				                         count[0] = a_comps.size() * box.numPts();
				
			}
			           assert(count[0] > 0);
			           int size = count[0] * type_size[i];
			           if (size > bufferCapacity[i])
				             {
				               free(buffers[i]);
				               bufferCapacity[i] = Max(2 * bufferCapacity[i], size);
				               buffers[i] = malloc(bufferCapacity[i]);
				               if (buffers[i] == NULL) {
					                                 MayDay::Error("memory error in buffer allocation read");
					
				}
				             }
			
				           err = H5Sselect_hyperslab(dataspace[i], H5S_SELECT_SET,
					                                      offset, NULL,
					                                      count, NULL);
			           assert(err >= 0);
			           hid_t memdataspace = H5Screate_simple(1, count, NULL);
           assert(memdataspace >= 0);
           err = H5Dread(dataset[i], types[i], memdataspace, dataspace[i],
                          H5P_DEFAULT, buffers[i]);
           assert(err >= 0);
           H5Sclose(memdataspace);
           if (err < 0) { ret = err; goto cleanup; }
         }
       box.grow(outputGhost);
       read(data, buffers, box, comps);
     }

  cleanup:
   for (unsigned int i = 0; i<types.size(); ++i)
     {
       free(buffers[i]);
       H5Sclose(dataspace[i]);
       H5Dclose(dataset[i]);
     }
   return ret;
 }


 template <class T>
 int writeLevel(HDF5Handle& a_handle,
                const int&  a_level,
                const LevelData<T>& a_data,
                const Real& a_dx,
                const Real& a_dt,
                const Real& a_time,
                const Box&  a_domain,
                const int&  a_refRatio,
                const IntVect& outputGhost)
 {
   int error;
   char levelName[10];
   std::string currentGroup = a_handle.getGroup();
   sprintf(levelName, "/level_%i", a_level);
  error = a_handle.setGroup(currentGroup + levelName);
   if (error != 0) return 1;

   HDF5HeaderData meta;
   meta.m_real["dx"] = a_dx;
   meta.m_real["dt"] = a_dt;
   meta.m_real["time"] = a_time;
   meta.m_box["prob_domain"] = a_domain;
   meta.m_int["ref_ratio"] = a_refRatio;

   error = meta.writeToFile(a_handle);
   if (error != 0) return 2;

   error = write(a_handle, a_data.boxLayout());
   if (error != 0) return 3;

  error = write(a_handle, a_data, "data", outputGhost);
  if (error != 0) return 4;
  a_handle.setGroup(currentGroup);

   return 0;
 }


 template <class T>
 int readLevel(HDF5Handle&   a_handle,
               const int&    a_level,
               LevelData<T>& a_data,
               Real& a_dx,
               Real& a_dt,
               Real& a_time,
               Box&  a_domain,
               int&  a_refRatio,
               const Interval&   a_comps,
               const IntVect& ghost,
               bool  setGhost)
 {
   HDF5HeaderData header;
   header.readFromFile(a_handle);
   int nComp = header.m_int["num_components"];

   int error;
   char levelName[10];
   std::string currentGroup = a_handle.getGroup();
   sprintf(levelName, "/level_%i", a_level);
   error = a_handle.setGroup(currentGroup + levelName);
   if (error != 0) return 1;

   HDF5HeaderData meta;
   error = meta.readFromFile(a_handle);
   if (error != 0) return 2;
   a_dx = meta.m_real["dx"];
   a_dt = meta.m_real["dt"];
   a_time = meta.m_real["time"];
   a_domain = meta.m_box["prob_domain"];
   a_refRatio = meta.m_int["ref_ratio"];

   Vector<Box> boxes;
   error = read(a_handle, boxes);
   Vector<int> procIDs;
   LoadBalance(procIDs, boxes);

   DisjointBoxLayout layout(boxes, procIDs);

   layout.close();
   if (error != 0) return 3;

   if (!setGhost)
     error = read(a_handle, a_data, "data", layout, a_comps);
   else
     {
           if (a_comps.size() != 0)
                 a_data.define(layout, a_comps.size(), ghost);
           else
                 a_data.define(layout, nComp, ghost);

           error = read(a_handle, a_data, "data", layout, a_comps, false);

     }
   if (error != 0) return 4;

   a_handle.setGroup(currentGroup);

   return 0;
 }



#endif  // HDF5_H

#endif // HDF5
