#include "PhoneBook.h"

PhoneBook::PersonalInfo::PersonalInfo(void) {
    std::memset(this, 0x00, sizeof(PersonalInfo));
}

PhoneBook::PersonalInfo::~PersonalInfo(void) {
    std::memset(this, 0x00, sizeof(PersonalInfo));
}

PhoneBook::PhoneBook(void) {
    this->personal_info_point = 0;
}

void PhoneBook::add(
        const PersonalInfo &personal_info) {
    this->personal_info[this->personal_info_point ++] = personal_info;
    if (this->personal_info_point == PHONE_BOOK_PERSONAL_INFO_SIZE)
        this->personal_info_point = 0;
}

const PhoneBook::PersonalInfo *PhoneBook::search(
        const char *const phone_number,
        const std::size_t count) {
    bool            flag;
    std::size_t     n = 0;      // 何回出現したか

    for (std::size_t j = 0; j < PHONE_BOOK_PERSONAL_INFO_SIZE; j ++) {
        // 登録されている電話番号が同等か確かめる
        flag = !std::strcmp(this->personal_info[j].phone_number, phone_number);

        // 登録されていて、count が n と同等のときアドレスを返す
        if (flag && count == n ++)
            return (&this->personal_info[j]);
    }

    // 存在しないから nullptr を返す
    return NULL;
}
