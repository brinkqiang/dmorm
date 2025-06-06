// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: person.proto
// Protobuf C++ Version: 5.26.1

#ifndef GOOGLE_PROTOBUF_INCLUDED_person_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_person_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>
#include <utility>

#include "google/protobuf/port_def.inc"
#if PROTOBUF_VERSION != 5026001
#error "Protobuf C++ gencode is built with an incompatible version of"
#error "Protobuf C++ headers/runtime. See"
#error "https://protobuf.dev/support/cross-version-runtime-guarantee/#cpp"
#endif
#include "google/protobuf/port_undef.inc"
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_tctable_decl.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/generated_enum_reflection.h"
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_person_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_person_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_person_2eproto;
namespace db {
class tb_Person;
struct tb_PersonDefaultTypeInternal;
extern tb_PersonDefaultTypeInternal _tb_Person_default_instance_;
}  // namespace db
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace db {
enum PhoneType : int {
  MOBILE = 0,
  HOME = 1,
  WORK = 2,
};

bool PhoneType_IsValid(int value);
extern const uint32_t PhoneType_internal_data_[];
constexpr PhoneType PhoneType_MIN = static_cast<PhoneType>(0);
constexpr PhoneType PhoneType_MAX = static_cast<PhoneType>(2);
constexpr int PhoneType_ARRAYSIZE = 2 + 1;
const ::google::protobuf::EnumDescriptor*
PhoneType_descriptor();
template <typename T>
const std::string& PhoneType_Name(T value) {
  static_assert(std::is_same<T, PhoneType>::value ||
                    std::is_integral<T>::value,
                "Incorrect type passed to PhoneType_Name().");
  return PhoneType_Name(static_cast<PhoneType>(value));
}
template <>
inline const std::string& PhoneType_Name(PhoneType value) {
  return ::google::protobuf::internal::NameOfDenseEnum<PhoneType_descriptor,
                                                 0, 2>(
      static_cast<int>(value));
}
inline bool PhoneType_Parse(absl::string_view name, PhoneType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<PhoneType>(
      PhoneType_descriptor(), name, value);
}

// ===================================================================


// -------------------------------------------------------------------

class tb_Person final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:db.tb_Person) */ {
 public:
  inline tb_Person() : tb_Person(nullptr) {}
  ~tb_Person() override;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR tb_Person(
      ::google::protobuf::internal::ConstantInitialized);

  inline tb_Person(const tb_Person& from) : tb_Person(nullptr, from) {}
  inline tb_Person(tb_Person&& from) noexcept
      : tb_Person(nullptr, std::move(from)) {}
  inline tb_Person& operator=(const tb_Person& from) {
    CopyFrom(from);
    return *this;
  }
  inline tb_Person& operator=(tb_Person&& from) noexcept {
    if (this == &from) return *this;
    if (GetArena() == from.GetArena()
#ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetArena() != nullptr
#endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const tb_Person& default_instance() {
    return *internal_default_instance();
  }
  static inline const tb_Person* internal_default_instance() {
    return reinterpret_cast<const tb_Person*>(
        &_tb_Person_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;
  friend void swap(tb_Person& a, tb_Person& b) { a.Swap(&b); }
  inline void Swap(tb_Person* other) {
    if (other == this) return;
#ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() != nullptr && GetArena() == other->GetArena()) {
#else   // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() == other->GetArena()) {
#endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(tb_Person* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  tb_Person* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::Message::DefaultConstruct<tb_Person>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const tb_Person& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const tb_Person& from) { tb_Person::MergeImpl(*this, from); }

  private:
  static void MergeImpl(
      ::google::protobuf::MessageLite& to_msg,
      const ::google::protobuf::MessageLite& from_msg);

  public:
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::google::protobuf::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void InternalSwap(tb_Person* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "db.tb_Person"; }

 protected:
  explicit tb_Person(::google::protobuf::Arena* arena);
  tb_Person(::google::protobuf::Arena* arena, const tb_Person& from);
  tb_Person(::google::protobuf::Arena* arena, tb_Person&& from) noexcept
      : tb_Person(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::MessageLite::ClassData* GetClassData()
      const final;

 public:
  ::google::protobuf::Metadata GetMetadata() const final;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kNumberFieldNumber = 2,
    kEmailFieldNumber = 3,
    kIdFieldNumber = 1,
    kPhonetypeFieldNumber = 4,
  };
  // optional string number = 2;
  bool has_number() const;
  void clear_number() ;
  const std::string& number() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_number(Arg_&& arg, Args_... args);
  std::string* mutable_number();
  PROTOBUF_NODISCARD std::string* release_number();
  void set_allocated_number(std::string* value);

  private:
  const std::string& _internal_number() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_number(
      const std::string& value);
  std::string* _internal_mutable_number();

  public:
  // optional string email = 3;
  bool has_email() const;
  void clear_email() ;
  const std::string& email() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_email(Arg_&& arg, Args_... args);
  std::string* mutable_email();
  PROTOBUF_NODISCARD std::string* release_email();
  void set_allocated_email(std::string* value);

  private:
  const std::string& _internal_email() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_email(
      const std::string& value);
  std::string* _internal_mutable_email();

  public:
  // optional uint64 id = 1;
  bool has_id() const;
  void clear_id() ;
  ::uint64_t id() const;
  void set_id(::uint64_t value);

  private:
  ::uint64_t _internal_id() const;
  void _internal_set_id(::uint64_t value);

  public:
  // optional .db.PhoneType phonetype = 4;
  bool has_phonetype() const;
  void clear_phonetype() ;
  ::db::PhoneType phonetype() const;
  void set_phonetype(::db::PhoneType value);

  private:
  ::db::PhoneType _internal_phonetype() const;
  void _internal_set_phonetype(::db::PhoneType value);

  public:
  // @@protoc_insertion_point(class_scope:db.tb_Person)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      2, 4, 1,
      32, 2>
      _table_;
  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from);
    ::google::protobuf::internal::HasBits<1> _has_bits_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    ::google::protobuf::internal::ArenaStringPtr number_;
    ::google::protobuf::internal::ArenaStringPtr email_;
    ::uint64_t id_;
    int phonetype_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_person_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// tb_Person

// optional uint64 id = 1;
inline bool tb_Person::has_id() const {
  bool value = (_impl_._has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline void tb_Person::clear_id() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.id_ = ::uint64_t{0u};
  _impl_._has_bits_[0] &= ~0x00000004u;
}
inline ::uint64_t tb_Person::id() const {
  // @@protoc_insertion_point(field_get:db.tb_Person.id)
  return _internal_id();
}
inline void tb_Person::set_id(::uint64_t value) {
  _internal_set_id(value);
  _impl_._has_bits_[0] |= 0x00000004u;
  // @@protoc_insertion_point(field_set:db.tb_Person.id)
}
inline ::uint64_t tb_Person::_internal_id() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.id_;
}
inline void tb_Person::_internal_set_id(::uint64_t value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.id_ = value;
}

// optional string number = 2;
inline bool tb_Person::has_number() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline void tb_Person::clear_number() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.number_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline const std::string& tb_Person::number() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:db.tb_Person.number)
  return _internal_number();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void tb_Person::set_number(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000001u;
  _impl_.number_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:db.tb_Person.number)
}
inline std::string* tb_Person::mutable_number() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_number();
  // @@protoc_insertion_point(field_mutable:db.tb_Person.number)
  return _s;
}
inline const std::string& tb_Person::_internal_number() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.number_.Get();
}
inline void tb_Person::_internal_set_number(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000001u;
  _impl_.number_.Set(value, GetArena());
}
inline std::string* tb_Person::_internal_mutable_number() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000001u;
  return _impl_.number_.Mutable( GetArena());
}
inline std::string* tb_Person::release_number() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:db.tb_Person.number)
  if ((_impl_._has_bits_[0] & 0x00000001u) == 0) {
    return nullptr;
  }
  _impl_._has_bits_[0] &= ~0x00000001u;
  auto* released = _impl_.number_.Release();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.number_.Set("", GetArena());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  return released;
}
inline void tb_Person::set_allocated_number(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (value != nullptr) {
    _impl_._has_bits_[0] |= 0x00000001u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000001u;
  }
  _impl_.number_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.number_.IsDefault()) {
          _impl_.number_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:db.tb_Person.number)
}

// optional string email = 3;
inline bool tb_Person::has_email() const {
  bool value = (_impl_._has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline void tb_Person::clear_email() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.email_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000002u;
}
inline const std::string& tb_Person::email() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:db.tb_Person.email)
  return _internal_email();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void tb_Person::set_email(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000002u;
  _impl_.email_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:db.tb_Person.email)
}
inline std::string* tb_Person::mutable_email() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_email();
  // @@protoc_insertion_point(field_mutable:db.tb_Person.email)
  return _s;
}
inline const std::string& tb_Person::_internal_email() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.email_.Get();
}
inline void tb_Person::_internal_set_email(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000002u;
  _impl_.email_.Set(value, GetArena());
}
inline std::string* tb_Person::_internal_mutable_email() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000002u;
  return _impl_.email_.Mutable( GetArena());
}
inline std::string* tb_Person::release_email() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:db.tb_Person.email)
  if ((_impl_._has_bits_[0] & 0x00000002u) == 0) {
    return nullptr;
  }
  _impl_._has_bits_[0] &= ~0x00000002u;
  auto* released = _impl_.email_.Release();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.email_.Set("", GetArena());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  return released;
}
inline void tb_Person::set_allocated_email(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (value != nullptr) {
    _impl_._has_bits_[0] |= 0x00000002u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000002u;
  }
  _impl_.email_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.email_.IsDefault()) {
          _impl_.email_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:db.tb_Person.email)
}

// optional .db.PhoneType phonetype = 4;
inline bool tb_Person::has_phonetype() const {
  bool value = (_impl_._has_bits_[0] & 0x00000008u) != 0;
  return value;
}
inline void tb_Person::clear_phonetype() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.phonetype_ = 0;
  _impl_._has_bits_[0] &= ~0x00000008u;
}
inline ::db::PhoneType tb_Person::phonetype() const {
  // @@protoc_insertion_point(field_get:db.tb_Person.phonetype)
  return _internal_phonetype();
}
inline void tb_Person::set_phonetype(::db::PhoneType value) {
  _internal_set_phonetype(value);
  _impl_._has_bits_[0] |= 0x00000008u;
  // @@protoc_insertion_point(field_set:db.tb_Person.phonetype)
}
inline ::db::PhoneType tb_Person::_internal_phonetype() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return static_cast<::db::PhoneType>(_impl_.phonetype_);
}
inline void tb_Person::_internal_set_phonetype(::db::PhoneType value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  assert(::db::PhoneType_IsValid(value));
  _impl_.phonetype_ = value;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace db


namespace google {
namespace protobuf {

template <>
struct is_proto_enum<::db::PhoneType> : std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor<::db::PhoneType>() {
  return ::db::PhoneType_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_person_2eproto_2epb_2eh
