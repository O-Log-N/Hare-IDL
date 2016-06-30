// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: output.proto

#ifndef PROTOBUF_output_2eproto__INCLUDED
#define PROTOBUF_output_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace pb {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_output_2eproto();
void protobuf_AssignDesc_output_2eproto();
void protobuf_ShutdownFile_output_2eproto();

class Item;
class Character;

// ===================================================================

class Item : public ::google::protobuf::Message {
 public:
  Item();
  virtual ~Item();

  Item(const Item& from);

  inline Item& operator=(const Item& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Item& default_instance();

  void Swap(Item* other);

  // implements Message ----------------------------------------------

  Item* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Item& from);
  void MergeFrom(const Item& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional uint32 id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::uint32 id() const;
  inline void set_id(::google::protobuf::uint32 value);

  // optional string name = 2;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 2;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // optional bool valid = 3;
  inline bool has_valid() const;
  inline void clear_valid();
  static const int kValidFieldNumber = 3;
  inline bool valid() const;
  inline void set_valid(bool value);

  // @@protoc_insertion_point(class_scope:pb.Item)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_valid();
  inline void clear_has_valid();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* name_;
  ::google::protobuf::uint32 id_;
  bool valid_;
  friend void  protobuf_AddDesc_output_2eproto();
  friend void protobuf_AssignDesc_output_2eproto();
  friend void protobuf_ShutdownFile_output_2eproto();

  void InitAsDefaultInstance();
  static Item* default_instance_;
};
// -------------------------------------------------------------------

class Character : public ::google::protobuf::Message {
 public:
  Character();
  virtual ~Character();

  Character(const Character& from);

  inline Character& operator=(const Character& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Character& default_instance();

  void Swap(Character* other);

  // implements Message ----------------------------------------------

  Character* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Character& from);
  void MergeFrom(const Character& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional uint32 max_u8 = 1;
  inline bool has_max_u8() const;
  inline void clear_max_u8();
  static const int kMaxU8FieldNumber = 1;
  inline ::google::protobuf::uint32 max_u8() const;
  inline void set_max_u8(::google::protobuf::uint32 value);

  // optional uint32 max_u16 = 2;
  inline bool has_max_u16() const;
  inline void clear_max_u16();
  static const int kMaxU16FieldNumber = 2;
  inline ::google::protobuf::uint32 max_u16() const;
  inline void set_max_u16(::google::protobuf::uint32 value);

  // optional uint32 max_u32 = 3;
  inline bool has_max_u32() const;
  inline void clear_max_u32();
  static const int kMaxU32FieldNumber = 3;
  inline ::google::protobuf::uint32 max_u32() const;
  inline void set_max_u32(::google::protobuf::uint32 value);

  // optional sint32 min_s8 = 4;
  inline bool has_min_s8() const;
  inline void clear_min_s8();
  static const int kMinS8FieldNumber = 4;
  inline ::google::protobuf::int32 min_s8() const;
  inline void set_min_s8(::google::protobuf::int32 value);

  // optional sint32 min_s16 = 5;
  inline bool has_min_s16() const;
  inline void clear_min_s16();
  static const int kMinS16FieldNumber = 5;
  inline ::google::protobuf::int32 min_s16() const;
  inline void set_min_s16(::google::protobuf::int32 value);

  // optional sint32 min_s32 = 6;
  inline bool has_min_s32() const;
  inline void clear_min_s32();
  static const int kMinS32FieldNumber = 6;
  inline ::google::protobuf::int32 min_s32() const;
  inline void set_min_s32(::google::protobuf::int32 value);

  // optional sint32 max_s8 = 7;
  inline bool has_max_s8() const;
  inline void clear_max_s8();
  static const int kMaxS8FieldNumber = 7;
  inline ::google::protobuf::int32 max_s8() const;
  inline void set_max_s8(::google::protobuf::int32 value);

  // optional sint32 max_s16 = 8;
  inline bool has_max_s16() const;
  inline void clear_max_s16();
  static const int kMaxS16FieldNumber = 8;
  inline ::google::protobuf::int32 max_s16() const;
  inline void set_max_s16(::google::protobuf::int32 value);

  // optional sint32 max_s32 = 9;
  inline bool has_max_s32() const;
  inline void clear_max_s32();
  static const int kMaxS32FieldNumber = 9;
  inline ::google::protobuf::int32 max_s32() const;
  inline void set_max_s32(::google::protobuf::int32 value);

  // optional double x = 10;
  inline bool has_x() const;
  inline void clear_x();
  static const int kXFieldNumber = 10;
  inline double x() const;
  inline void set_x(double value);

  // optional double y = 11;
  inline bool has_y() const;
  inline void clear_y();
  static const int kYFieldNumber = 11;
  inline double y() const;
  inline void set_y(double value);

  // optional double z = 12;
  inline bool has_z() const;
  inline void clear_z();
  static const int kZFieldNumber = 12;
  inline double z() const;
  inline void set_z(double value);

  // optional bool flag = 13;
  inline bool has_flag() const;
  inline void clear_flag();
  static const int kFlagFieldNumber = 13;
  inline bool flag() const;
  inline void set_flag(bool value);

  // optional string desc = 14;
  inline bool has_desc() const;
  inline void clear_desc();
  static const int kDescFieldNumber = 14;
  inline const ::std::string& desc() const;
  inline void set_desc(const ::std::string& value);
  inline void set_desc(const char* value);
  inline void set_desc(const char* value, size_t size);
  inline ::std::string* mutable_desc();
  inline ::std::string* release_desc();
  inline void set_allocated_desc(::std::string* desc);

  // repeated string more_text = 15;
  inline int more_text_size() const;
  inline void clear_more_text();
  static const int kMoreTextFieldNumber = 15;
  inline const ::std::string& more_text(int index) const;
  inline ::std::string* mutable_more_text(int index);
  inline void set_more_text(int index, const ::std::string& value);
  inline void set_more_text(int index, const char* value);
  inline void set_more_text(int index, const char* value, size_t size);
  inline ::std::string* add_more_text();
  inline void add_more_text(const ::std::string& value);
  inline void add_more_text(const char* value);
  inline void add_more_text(const char* value, size_t size);
  inline const ::google::protobuf::RepeatedPtrField< ::std::string>& more_text() const;
  inline ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_more_text();

  // repeated sint32 some_ints = 16;
  inline int some_ints_size() const;
  inline void clear_some_ints();
  static const int kSomeIntsFieldNumber = 16;
  inline ::google::protobuf::int32 some_ints(int index) const;
  inline void set_some_ints(int index, ::google::protobuf::int32 value);
  inline void add_some_ints(::google::protobuf::int32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
      some_ints() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
      mutable_some_ints();

  // repeated .pb.Item inventory = 17;
  inline int inventory_size() const;
  inline void clear_inventory();
  static const int kInventoryFieldNumber = 17;
  inline const ::pb::Item& inventory(int index) const;
  inline ::pb::Item* mutable_inventory(int index);
  inline ::pb::Item* add_inventory();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::Item >&
      inventory() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::Item >*
      mutable_inventory();

  // @@protoc_insertion_point(class_scope:pb.Character)
 private:
  inline void set_has_max_u8();
  inline void clear_has_max_u8();
  inline void set_has_max_u16();
  inline void clear_has_max_u16();
  inline void set_has_max_u32();
  inline void clear_has_max_u32();
  inline void set_has_min_s8();
  inline void clear_has_min_s8();
  inline void set_has_min_s16();
  inline void clear_has_min_s16();
  inline void set_has_min_s32();
  inline void clear_has_min_s32();
  inline void set_has_max_s8();
  inline void clear_has_max_s8();
  inline void set_has_max_s16();
  inline void clear_has_max_s16();
  inline void set_has_max_s32();
  inline void clear_has_max_s32();
  inline void set_has_x();
  inline void clear_has_x();
  inline void set_has_y();
  inline void clear_has_y();
  inline void set_has_z();
  inline void clear_has_z();
  inline void set_has_flag();
  inline void clear_has_flag();
  inline void set_has_desc();
  inline void clear_has_desc();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 max_u8_;
  ::google::protobuf::uint32 max_u16_;
  ::google::protobuf::uint32 max_u32_;
  ::google::protobuf::int32 min_s8_;
  ::google::protobuf::int32 min_s16_;
  ::google::protobuf::int32 min_s32_;
  ::google::protobuf::int32 max_s8_;
  ::google::protobuf::int32 max_s16_;
  double x_;
  double y_;
  ::google::protobuf::int32 max_s32_;
  bool flag_;
  double z_;
  ::std::string* desc_;
  ::google::protobuf::RepeatedPtrField< ::std::string> more_text_;
  ::google::protobuf::RepeatedField< ::google::protobuf::int32 > some_ints_;
  ::google::protobuf::RepeatedPtrField< ::pb::Item > inventory_;
  friend void  protobuf_AddDesc_output_2eproto();
  friend void protobuf_AssignDesc_output_2eproto();
  friend void protobuf_ShutdownFile_output_2eproto();

  void InitAsDefaultInstance();
  static Character* default_instance_;
};
// ===================================================================


// ===================================================================

// Item

// optional uint32 id = 1;
inline bool Item::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Item::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Item::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Item::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 Item::id() const {
  // @@protoc_insertion_point(field_get:pb.Item.id)
  return id_;
}
inline void Item::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:pb.Item.id)
}

// optional string name = 2;
inline bool Item::has_name() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Item::set_has_name() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Item::clear_has_name() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Item::clear_name() {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& Item::name() const {
  // @@protoc_insertion_point(field_get:pb.Item.name)
  return *name_;
}
inline void Item::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(value);
  // @@protoc_insertion_point(field_set:pb.Item.name)
}
inline void Item::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(value);
  // @@protoc_insertion_point(field_set_char:pb.Item.name)
}
inline void Item::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:pb.Item.name)
}
inline ::std::string* Item::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:pb.Item.name)
  return name_;
}
inline ::std::string* Item::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void Item::set_allocated_name(::std::string* name) {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete name_;
  }
  if (name) {
    set_has_name();
    name_ = name;
  } else {
    clear_has_name();
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:pb.Item.name)
}

// optional bool valid = 3;
inline bool Item::has_valid() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Item::set_has_valid() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Item::clear_has_valid() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Item::clear_valid() {
  valid_ = false;
  clear_has_valid();
}
inline bool Item::valid() const {
  // @@protoc_insertion_point(field_get:pb.Item.valid)
  return valid_;
}
inline void Item::set_valid(bool value) {
  set_has_valid();
  valid_ = value;
  // @@protoc_insertion_point(field_set:pb.Item.valid)
}

// -------------------------------------------------------------------

// Character

// optional uint32 max_u8 = 1;
inline bool Character::has_max_u8() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Character::set_has_max_u8() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Character::clear_has_max_u8() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Character::clear_max_u8() {
  max_u8_ = 0u;
  clear_has_max_u8();
}
inline ::google::protobuf::uint32 Character::max_u8() const {
  // @@protoc_insertion_point(field_get:pb.Character.max_u8)
  return max_u8_;
}
inline void Character::set_max_u8(::google::protobuf::uint32 value) {
  set_has_max_u8();
  max_u8_ = value;
  // @@protoc_insertion_point(field_set:pb.Character.max_u8)
}

// optional uint32 max_u16 = 2;
inline bool Character::has_max_u16() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Character::set_has_max_u16() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Character::clear_has_max_u16() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Character::clear_max_u16() {
  max_u16_ = 0u;
  clear_has_max_u16();
}
inline ::google::protobuf::uint32 Character::max_u16() const {
  // @@protoc_insertion_point(field_get:pb.Character.max_u16)
  return max_u16_;
}
inline void Character::set_max_u16(::google::protobuf::uint32 value) {
  set_has_max_u16();
  max_u16_ = value;
  // @@protoc_insertion_point(field_set:pb.Character.max_u16)
}

// optional uint32 max_u32 = 3;
inline bool Character::has_max_u32() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Character::set_has_max_u32() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Character::clear_has_max_u32() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Character::clear_max_u32() {
  max_u32_ = 0u;
  clear_has_max_u32();
}
inline ::google::protobuf::uint32 Character::max_u32() const {
  // @@protoc_insertion_point(field_get:pb.Character.max_u32)
  return max_u32_;
}
inline void Character::set_max_u32(::google::protobuf::uint32 value) {
  set_has_max_u32();
  max_u32_ = value;
  // @@protoc_insertion_point(field_set:pb.Character.max_u32)
}

// optional sint32 min_s8 = 4;
inline bool Character::has_min_s8() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Character::set_has_min_s8() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Character::clear_has_min_s8() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Character::clear_min_s8() {
  min_s8_ = 0;
  clear_has_min_s8();
}
inline ::google::protobuf::int32 Character::min_s8() const {
  // @@protoc_insertion_point(field_get:pb.Character.min_s8)
  return min_s8_;
}
inline void Character::set_min_s8(::google::protobuf::int32 value) {
  set_has_min_s8();
  min_s8_ = value;
  // @@protoc_insertion_point(field_set:pb.Character.min_s8)
}

// optional sint32 min_s16 = 5;
inline bool Character::has_min_s16() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Character::set_has_min_s16() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Character::clear_has_min_s16() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Character::clear_min_s16() {
  min_s16_ = 0;
  clear_has_min_s16();
}
inline ::google::protobuf::int32 Character::min_s16() const {
  // @@protoc_insertion_point(field_get:pb.Character.min_s16)
  return min_s16_;
}
inline void Character::set_min_s16(::google::protobuf::int32 value) {
  set_has_min_s16();
  min_s16_ = value;
  // @@protoc_insertion_point(field_set:pb.Character.min_s16)
}

// optional sint32 min_s32 = 6;
inline bool Character::has_min_s32() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void Character::set_has_min_s32() {
  _has_bits_[0] |= 0x00000020u;
}
inline void Character::clear_has_min_s32() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void Character::clear_min_s32() {
  min_s32_ = 0;
  clear_has_min_s32();
}
inline ::google::protobuf::int32 Character::min_s32() const {
  // @@protoc_insertion_point(field_get:pb.Character.min_s32)
  return min_s32_;
}
inline void Character::set_min_s32(::google::protobuf::int32 value) {
  set_has_min_s32();
  min_s32_ = value;
  // @@protoc_insertion_point(field_set:pb.Character.min_s32)
}

// optional sint32 max_s8 = 7;
inline bool Character::has_max_s8() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void Character::set_has_max_s8() {
  _has_bits_[0] |= 0x00000040u;
}
inline void Character::clear_has_max_s8() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void Character::clear_max_s8() {
  max_s8_ = 0;
  clear_has_max_s8();
}
inline ::google::protobuf::int32 Character::max_s8() const {
  // @@protoc_insertion_point(field_get:pb.Character.max_s8)
  return max_s8_;
}
inline void Character::set_max_s8(::google::protobuf::int32 value) {
  set_has_max_s8();
  max_s8_ = value;
  // @@protoc_insertion_point(field_set:pb.Character.max_s8)
}

// optional sint32 max_s16 = 8;
inline bool Character::has_max_s16() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void Character::set_has_max_s16() {
  _has_bits_[0] |= 0x00000080u;
}
inline void Character::clear_has_max_s16() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void Character::clear_max_s16() {
  max_s16_ = 0;
  clear_has_max_s16();
}
inline ::google::protobuf::int32 Character::max_s16() const {
  // @@protoc_insertion_point(field_get:pb.Character.max_s16)
  return max_s16_;
}
inline void Character::set_max_s16(::google::protobuf::int32 value) {
  set_has_max_s16();
  max_s16_ = value;
  // @@protoc_insertion_point(field_set:pb.Character.max_s16)
}

// optional sint32 max_s32 = 9;
inline bool Character::has_max_s32() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void Character::set_has_max_s32() {
  _has_bits_[0] |= 0x00000100u;
}
inline void Character::clear_has_max_s32() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void Character::clear_max_s32() {
  max_s32_ = 0;
  clear_has_max_s32();
}
inline ::google::protobuf::int32 Character::max_s32() const {
  // @@protoc_insertion_point(field_get:pb.Character.max_s32)
  return max_s32_;
}
inline void Character::set_max_s32(::google::protobuf::int32 value) {
  set_has_max_s32();
  max_s32_ = value;
  // @@protoc_insertion_point(field_set:pb.Character.max_s32)
}

// optional double x = 10;
inline bool Character::has_x() const {
  return (_has_bits_[0] & 0x00000200u) != 0;
}
inline void Character::set_has_x() {
  _has_bits_[0] |= 0x00000200u;
}
inline void Character::clear_has_x() {
  _has_bits_[0] &= ~0x00000200u;
}
inline void Character::clear_x() {
  x_ = 0;
  clear_has_x();
}
inline double Character::x() const {
  // @@protoc_insertion_point(field_get:pb.Character.x)
  return x_;
}
inline void Character::set_x(double value) {
  set_has_x();
  x_ = value;
  // @@protoc_insertion_point(field_set:pb.Character.x)
}

// optional double y = 11;
inline bool Character::has_y() const {
  return (_has_bits_[0] & 0x00000400u) != 0;
}
inline void Character::set_has_y() {
  _has_bits_[0] |= 0x00000400u;
}
inline void Character::clear_has_y() {
  _has_bits_[0] &= ~0x00000400u;
}
inline void Character::clear_y() {
  y_ = 0;
  clear_has_y();
}
inline double Character::y() const {
  // @@protoc_insertion_point(field_get:pb.Character.y)
  return y_;
}
inline void Character::set_y(double value) {
  set_has_y();
  y_ = value;
  // @@protoc_insertion_point(field_set:pb.Character.y)
}

// optional double z = 12;
inline bool Character::has_z() const {
  return (_has_bits_[0] & 0x00000800u) != 0;
}
inline void Character::set_has_z() {
  _has_bits_[0] |= 0x00000800u;
}
inline void Character::clear_has_z() {
  _has_bits_[0] &= ~0x00000800u;
}
inline void Character::clear_z() {
  z_ = 0;
  clear_has_z();
}
inline double Character::z() const {
  // @@protoc_insertion_point(field_get:pb.Character.z)
  return z_;
}
inline void Character::set_z(double value) {
  set_has_z();
  z_ = value;
  // @@protoc_insertion_point(field_set:pb.Character.z)
}

// optional bool flag = 13;
inline bool Character::has_flag() const {
  return (_has_bits_[0] & 0x00001000u) != 0;
}
inline void Character::set_has_flag() {
  _has_bits_[0] |= 0x00001000u;
}
inline void Character::clear_has_flag() {
  _has_bits_[0] &= ~0x00001000u;
}
inline void Character::clear_flag() {
  flag_ = false;
  clear_has_flag();
}
inline bool Character::flag() const {
  // @@protoc_insertion_point(field_get:pb.Character.flag)
  return flag_;
}
inline void Character::set_flag(bool value) {
  set_has_flag();
  flag_ = value;
  // @@protoc_insertion_point(field_set:pb.Character.flag)
}

// optional string desc = 14;
inline bool Character::has_desc() const {
  return (_has_bits_[0] & 0x00002000u) != 0;
}
inline void Character::set_has_desc() {
  _has_bits_[0] |= 0x00002000u;
}
inline void Character::clear_has_desc() {
  _has_bits_[0] &= ~0x00002000u;
}
inline void Character::clear_desc() {
  if (desc_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    desc_->clear();
  }
  clear_has_desc();
}
inline const ::std::string& Character::desc() const {
  // @@protoc_insertion_point(field_get:pb.Character.desc)
  return *desc_;
}
inline void Character::set_desc(const ::std::string& value) {
  set_has_desc();
  if (desc_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    desc_ = new ::std::string;
  }
  desc_->assign(value);
  // @@protoc_insertion_point(field_set:pb.Character.desc)
}
inline void Character::set_desc(const char* value) {
  set_has_desc();
  if (desc_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    desc_ = new ::std::string;
  }
  desc_->assign(value);
  // @@protoc_insertion_point(field_set_char:pb.Character.desc)
}
inline void Character::set_desc(const char* value, size_t size) {
  set_has_desc();
  if (desc_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    desc_ = new ::std::string;
  }
  desc_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:pb.Character.desc)
}
inline ::std::string* Character::mutable_desc() {
  set_has_desc();
  if (desc_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    desc_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:pb.Character.desc)
  return desc_;
}
inline ::std::string* Character::release_desc() {
  clear_has_desc();
  if (desc_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = desc_;
    desc_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void Character::set_allocated_desc(::std::string* desc) {
  if (desc_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete desc_;
  }
  if (desc) {
    set_has_desc();
    desc_ = desc;
  } else {
    clear_has_desc();
    desc_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:pb.Character.desc)
}

// repeated string more_text = 15;
inline int Character::more_text_size() const {
  return more_text_.size();
}
inline void Character::clear_more_text() {
  more_text_.Clear();
}
inline const ::std::string& Character::more_text(int index) const {
  // @@protoc_insertion_point(field_get:pb.Character.more_text)
  return more_text_.Get(index);
}
inline ::std::string* Character::mutable_more_text(int index) {
  // @@protoc_insertion_point(field_mutable:pb.Character.more_text)
  return more_text_.Mutable(index);
}
inline void Character::set_more_text(int index, const ::std::string& value) {
  // @@protoc_insertion_point(field_set:pb.Character.more_text)
  more_text_.Mutable(index)->assign(value);
}
inline void Character::set_more_text(int index, const char* value) {
  more_text_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:pb.Character.more_text)
}
inline void Character::set_more_text(int index, const char* value, size_t size) {
  more_text_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:pb.Character.more_text)
}
inline ::std::string* Character::add_more_text() {
  return more_text_.Add();
}
inline void Character::add_more_text(const ::std::string& value) {
  more_text_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:pb.Character.more_text)
}
inline void Character::add_more_text(const char* value) {
  more_text_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:pb.Character.more_text)
}
inline void Character::add_more_text(const char* value, size_t size) {
  more_text_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:pb.Character.more_text)
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
Character::more_text() const {
  // @@protoc_insertion_point(field_list:pb.Character.more_text)
  return more_text_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
Character::mutable_more_text() {
  // @@protoc_insertion_point(field_mutable_list:pb.Character.more_text)
  return &more_text_;
}

// repeated sint32 some_ints = 16;
inline int Character::some_ints_size() const {
  return some_ints_.size();
}
inline void Character::clear_some_ints() {
  some_ints_.Clear();
}
inline ::google::protobuf::int32 Character::some_ints(int index) const {
  // @@protoc_insertion_point(field_get:pb.Character.some_ints)
  return some_ints_.Get(index);
}
inline void Character::set_some_ints(int index, ::google::protobuf::int32 value) {
  some_ints_.Set(index, value);
  // @@protoc_insertion_point(field_set:pb.Character.some_ints)
}
inline void Character::add_some_ints(::google::protobuf::int32 value) {
  some_ints_.Add(value);
  // @@protoc_insertion_point(field_add:pb.Character.some_ints)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
Character::some_ints() const {
  // @@protoc_insertion_point(field_list:pb.Character.some_ints)
  return some_ints_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
Character::mutable_some_ints() {
  // @@protoc_insertion_point(field_mutable_list:pb.Character.some_ints)
  return &some_ints_;
}

// repeated .pb.Item inventory = 17;
inline int Character::inventory_size() const {
  return inventory_.size();
}
inline void Character::clear_inventory() {
  inventory_.Clear();
}
inline const ::pb::Item& Character::inventory(int index) const {
  // @@protoc_insertion_point(field_get:pb.Character.inventory)
  return inventory_.Get(index);
}
inline ::pb::Item* Character::mutable_inventory(int index) {
  // @@protoc_insertion_point(field_mutable:pb.Character.inventory)
  return inventory_.Mutable(index);
}
inline ::pb::Item* Character::add_inventory() {
  // @@protoc_insertion_point(field_add:pb.Character.inventory)
  return inventory_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::Item >&
Character::inventory() const {
  // @@protoc_insertion_point(field_list:pb.Character.inventory)
  return inventory_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::Item >*
Character::mutable_inventory() {
  // @@protoc_insertion_point(field_mutable_list:pb.Character.inventory)
  return &inventory_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_output_2eproto__INCLUDED
