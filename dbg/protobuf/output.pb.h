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
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace pb {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_output_2eproto();
void protobuf_AssignDesc_output_2eproto();
void protobuf_ShutdownFile_output_2eproto();

class Item;
class Character;

enum Character_Animation {
  Character_Animation_Running = 2,
  Character_Animation_Standing = 0,
  Character_Animation_Walking = 1
};
bool Character_Animation_IsValid(int value);
const Character_Animation Character_Animation_Animation_MIN = Character_Animation_Standing;
const Character_Animation Character_Animation_Animation_MAX = Character_Animation_Running;
const int Character_Animation_Animation_ARRAYSIZE = Character_Animation_Animation_MAX + 1;

const ::google::protobuf::EnumDescriptor* Character_Animation_descriptor();
inline const ::std::string& Character_Animation_Name(Character_Animation value) {
  return ::google::protobuf::internal::NameOfEnum(
    Character_Animation_descriptor(), value);
}
inline bool Character_Animation_Parse(
    const ::std::string& name, Character_Animation* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Character_Animation>(
    Character_Animation_descriptor(), name, value);
}
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

  // optional string name = 1;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 1;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // @@protoc_insertion_point(class_scope:pb.Item)
 private:
  inline void set_has_name();
  inline void clear_has_name();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* name_;
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

  typedef Character_Animation Animation;
  static const Animation Running = Character_Animation_Running;
  static const Animation Standing = Character_Animation_Standing;
  static const Animation Walking = Character_Animation_Walking;
  static inline bool Animation_IsValid(int value) {
    return Character_Animation_IsValid(value);
  }
  static const Animation Animation_MIN =
    Character_Animation_Animation_MIN;
  static const Animation Animation_MAX =
    Character_Animation_Animation_MAX;
  static const int Animation_ARRAYSIZE =
    Character_Animation_Animation_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Animation_descriptor() {
    return Character_Animation_descriptor();
  }
  static inline const ::std::string& Animation_Name(Animation value) {
    return Character_Animation_Name(value);
  }
  static inline bool Animation_Parse(const ::std::string& name,
      Animation* value) {
    return Character_Animation_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // optional uint64 character_id = 1;
  inline bool has_character_id() const;
  inline void clear_character_id();
  static const int kCharacterIdFieldNumber = 1;
  inline ::google::protobuf::uint64 character_id() const;
  inline void set_character_id(::google::protobuf::uint64 value);

  // optional double x = 2;
  inline bool has_x() const;
  inline void clear_x();
  static const int kXFieldNumber = 2;
  inline double x() const;
  inline void set_x(double value);

  // optional double y = 3;
  inline bool has_y() const;
  inline void clear_y();
  static const int kYFieldNumber = 3;
  inline double y() const;
  inline void set_y(double value);

  // optional double z = 4;
  inline bool has_z() const;
  inline void clear_z();
  static const int kZFieldNumber = 4;
  inline double z() const;
  inline void set_z(double value);

  // optional double vx = 5;
  inline bool has_vx() const;
  inline void clear_vx();
  static const int kVxFieldNumber = 5;
  inline double vx() const;
  inline void set_vx(double value);

  // optional double vy = 6;
  inline bool has_vy() const;
  inline void clear_vy();
  static const int kVyFieldNumber = 6;
  inline double vy() const;
  inline void set_vy(double value);

  // optional double vz = 7;
  inline bool has_vz() const;
  inline void clear_vz();
  static const int kVzFieldNumber = 7;
  inline double vz() const;
  inline void set_vz(double value);

  // optional double angle = 8;
  inline bool has_angle() const;
  inline void clear_angle();
  static const int kAngleFieldNumber = 8;
  inline double angle() const;
  inline void set_angle(double value);

  // optional .pb.Character.Animation anim = 9;
  inline bool has_anim() const;
  inline void clear_anim();
  static const int kAnimFieldNumber = 9;
  inline ::pb::Character_Animation anim() const;
  inline void set_anim(::pb::Character_Animation value);

  // optional uint64 animation_frame = 10;
  inline bool has_animation_frame() const;
  inline void clear_animation_frame();
  static const int kAnimationFrameFieldNumber = 10;
  inline ::google::protobuf::uint64 animation_frame() const;
  inline void set_animation_frame(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:pb.Character)
 private:
  inline void set_has_character_id();
  inline void clear_has_character_id();
  inline void set_has_x();
  inline void clear_has_x();
  inline void set_has_y();
  inline void clear_has_y();
  inline void set_has_z();
  inline void clear_has_z();
  inline void set_has_vx();
  inline void clear_has_vx();
  inline void set_has_vy();
  inline void clear_has_vy();
  inline void set_has_vz();
  inline void clear_has_vz();
  inline void set_has_angle();
  inline void clear_has_angle();
  inline void set_has_anim();
  inline void clear_has_anim();
  inline void set_has_animation_frame();
  inline void clear_has_animation_frame();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint64 character_id_;
  double x_;
  double y_;
  double z_;
  double vx_;
  double vy_;
  double vz_;
  double angle_;
  ::google::protobuf::uint64 animation_frame_;
  int anim_;
  friend void  protobuf_AddDesc_output_2eproto();
  friend void protobuf_AssignDesc_output_2eproto();
  friend void protobuf_ShutdownFile_output_2eproto();

  void InitAsDefaultInstance();
  static Character* default_instance_;
};
// ===================================================================


// ===================================================================

// Item

// optional string name = 1;
inline bool Item::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Item::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Item::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
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

// -------------------------------------------------------------------

// Character

// optional uint64 character_id = 1;
inline bool Character::has_character_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Character::set_has_character_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Character::clear_has_character_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Character::clear_character_id() {
  character_id_ = GOOGLE_ULONGLONG(0);
  clear_has_character_id();
}
inline ::google::protobuf::uint64 Character::character_id() const {
  // @@protoc_insertion_point(field_get:pb.Character.character_id)
  return character_id_;
}
inline void Character::set_character_id(::google::protobuf::uint64 value) {
  set_has_character_id();
  character_id_ = value;
  // @@protoc_insertion_point(field_set:pb.Character.character_id)
}

// optional double x = 2;
inline bool Character::has_x() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Character::set_has_x() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Character::clear_has_x() {
  _has_bits_[0] &= ~0x00000002u;
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

// optional double y = 3;
inline bool Character::has_y() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Character::set_has_y() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Character::clear_has_y() {
  _has_bits_[0] &= ~0x00000004u;
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

// optional double z = 4;
inline bool Character::has_z() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Character::set_has_z() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Character::clear_has_z() {
  _has_bits_[0] &= ~0x00000008u;
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

// optional double vx = 5;
inline bool Character::has_vx() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Character::set_has_vx() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Character::clear_has_vx() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Character::clear_vx() {
  vx_ = 0;
  clear_has_vx();
}
inline double Character::vx() const {
  // @@protoc_insertion_point(field_get:pb.Character.vx)
  return vx_;
}
inline void Character::set_vx(double value) {
  set_has_vx();
  vx_ = value;
  // @@protoc_insertion_point(field_set:pb.Character.vx)
}

// optional double vy = 6;
inline bool Character::has_vy() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void Character::set_has_vy() {
  _has_bits_[0] |= 0x00000020u;
}
inline void Character::clear_has_vy() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void Character::clear_vy() {
  vy_ = 0;
  clear_has_vy();
}
inline double Character::vy() const {
  // @@protoc_insertion_point(field_get:pb.Character.vy)
  return vy_;
}
inline void Character::set_vy(double value) {
  set_has_vy();
  vy_ = value;
  // @@protoc_insertion_point(field_set:pb.Character.vy)
}

// optional double vz = 7;
inline bool Character::has_vz() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void Character::set_has_vz() {
  _has_bits_[0] |= 0x00000040u;
}
inline void Character::clear_has_vz() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void Character::clear_vz() {
  vz_ = 0;
  clear_has_vz();
}
inline double Character::vz() const {
  // @@protoc_insertion_point(field_get:pb.Character.vz)
  return vz_;
}
inline void Character::set_vz(double value) {
  set_has_vz();
  vz_ = value;
  // @@protoc_insertion_point(field_set:pb.Character.vz)
}

// optional double angle = 8;
inline bool Character::has_angle() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void Character::set_has_angle() {
  _has_bits_[0] |= 0x00000080u;
}
inline void Character::clear_has_angle() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void Character::clear_angle() {
  angle_ = 0;
  clear_has_angle();
}
inline double Character::angle() const {
  // @@protoc_insertion_point(field_get:pb.Character.angle)
  return angle_;
}
inline void Character::set_angle(double value) {
  set_has_angle();
  angle_ = value;
  // @@protoc_insertion_point(field_set:pb.Character.angle)
}

// optional .pb.Character.Animation anim = 9;
inline bool Character::has_anim() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void Character::set_has_anim() {
  _has_bits_[0] |= 0x00000100u;
}
inline void Character::clear_has_anim() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void Character::clear_anim() {
  anim_ = 2;
  clear_has_anim();
}
inline ::pb::Character_Animation Character::anim() const {
  // @@protoc_insertion_point(field_get:pb.Character.anim)
  return static_cast< ::pb::Character_Animation >(anim_);
}
inline void Character::set_anim(::pb::Character_Animation value) {
  assert(::pb::Character_Animation_IsValid(value));
  set_has_anim();
  anim_ = value;
  // @@protoc_insertion_point(field_set:pb.Character.anim)
}

// optional uint64 animation_frame = 10;
inline bool Character::has_animation_frame() const {
  return (_has_bits_[0] & 0x00000200u) != 0;
}
inline void Character::set_has_animation_frame() {
  _has_bits_[0] |= 0x00000200u;
}
inline void Character::clear_has_animation_frame() {
  _has_bits_[0] &= ~0x00000200u;
}
inline void Character::clear_animation_frame() {
  animation_frame_ = GOOGLE_ULONGLONG(0);
  clear_has_animation_frame();
}
inline ::google::protobuf::uint64 Character::animation_frame() const {
  // @@protoc_insertion_point(field_get:pb.Character.animation_frame)
  return animation_frame_;
}
inline void Character::set_animation_frame(::google::protobuf::uint64 value) {
  set_has_animation_frame();
  animation_frame_ = value;
  // @@protoc_insertion_point(field_set:pb.Character.animation_frame)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::pb::Character_Animation> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::pb::Character_Animation>() {
  return ::pb::Character_Animation_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_output_2eproto__INCLUDED
