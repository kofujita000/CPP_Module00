#include "Contact.h"

void Contact::run(void) {
    bool                flag;
    Contact::Command    cmd = COMMAND_UNKNOWN;                 // コマンド
    char                cmd_str[CONTACT_INPUT_COMMAND_SIZE];    // コマンド (文字列)

    while (cmd != COMMAND_EXIT) {
        // コマンドを文字列で受け取る
        this->inputCommand(cmd_str);
        // 変換する
        flag = this->convertStringToCommand(cmd_str, cmd);
        if (!flag) {
            std::cout << CONTACT_INPUT_ERROR_MSG << std::endl;
            continue;
        }

        // 各コマンドを実行する
        switch (cmd) {
            case (COMMAND_ADD):
                flag = this->addPhoneBook();
                break;

            case (COMMAND_SEARCH):
                flag = this->searchPhoneBook();
                break;

            default:
                break;
        }
        if (!flag) {
            std::cout << CONTACT_INPUT_RANGE_MSG << std::endl;
        }
    }
}

void Contact::inputCommand(
        char cmd_str[CONTACT_INPUT_COMMAND_SIZE]) {
    std::cout << "Command: " << std::endl;
    this->inputParameter(cmd_str, 7);
}

bool Contact::convertStringToCommand(
                const char *const str,
                Contact::Command &cmd) {
    if (!std::strcmp(str, CONTACT_CMD_ADD)) {
        cmd = Contact::COMMAND_ADD;
    } else if (!std::strcmp(str, CONTACT_CMD_SEARCH)) {
        cmd = Contact::COMMAND_SEARCH;
    } else if (!std::strcmp(str, CONTACT_CMD_EXIT)) {
        cmd = Contact::COMMAND_EXIT;
    } else {
        cmd = Contact::COMMAND_UNKNOWN;
    }

    return (cmd != Contact::COMMAND_UNKNOWN);
}

bool Contact::addPhoneBook(void) {
    bool                    flag;
    PhoneBook::PersonalInfo personal_info;
    char                    buff[CONTACT_BUFF_SIZE];

    // first name の読み取り処理
    std::cout << " FirstName: " << std::endl;
    flag = this->inputParameter(buff, 11);
    std::memcpy(personal_info.first_name, buff, ::strlen(buff));

    // family name の読み取り処理
    std::cout << " FamilyName: " << std::endl;
    flag = this->inputParameter(buff, 11);
    std::memcpy(personal_info.family_name, buff, ::strlen(buff));

    // nick name の読み取り処理
    std::cout << " NickName: " << std::endl;
    flag = this->inputParameter(buff, 11);
    std::memcpy(personal_info.nick_name, buff, ::strlen(buff));

    // phone number の読み取り処理
    std::cout << " PhoneNumber(10): " << std::endl;
    flag = this->inputParameter(buff, 10);
    if (!flag) {
        return flag;
    }
    std::memcpy(personal_info.phone_number, buff, ::strlen(buff));

    // darkest secret の読み取り処理
    std::cout << " DarkestSecret: " << std::endl;
    flag = this->inputParameter(buff, 11);
    std::memcpy(personal_info.darkest_secret, buff, ::strlen(buff));

    // データを設定する
    this->phone_book.add(personal_info);

    return flag;
}

bool Contact::searchPhoneBook(void) {
    bool                            flag;
    const PhoneBook::PersonalInfo   *personal_info;
    char                            phone_number[CONTACT_BUFF_SIZE];
    char                            buff[16];

    flag = this->inputParameter(phone_number, 10);
    if (!flag) {
        return flag;
    }
    for (std::size_t count = 0; ; count ++) {
        personal_info = this->phone_book.search(phone_number, count);
        if (!personal_info)
            break;
        // 現在の番号を出力する
        std::cout << count << " | ";
        // first name の出力を行う
        this->makeOutputValue(buff, personal_info->first_name, 10);
        std::cout << buff << "| ";
        // family name の出力を行う
        this->makeOutputValue(buff, personal_info->family_name, 10);
        std::cout << buff << "| ";
        // nick name の出力を行う
        this->makeOutputValue(buff, personal_info->nick_name, 10);
        std::cout << buff << std::endl;
    }

    return flag;
}

bool Contact::inputParameter(
        char buff[CONTACT_BUFF_SIZE],
        const ::ssize_t max) {
    static ::size_t   buff_size = CONTACT_BUFF_SIZE;

    ::ssize_t               buff_len;
    char                    *buff_ptr = buff;

    buff_len = ::getline(&buff_ptr, &buff_size, stdin);
    if (buff[buff_len - 1] == '\n')
        buff_len --;
    if (buff_len < 0 || max < buff_len) {
        if (buff_len == CONTACT_BUFF_SIZE - 1) {
            this->clearRead();
        }
        buff[max] = 0x00;
        return false;
    }
    buff[buff_len] = 0x00;

    return true;
}

void Contact::makeOutputValue(
        char response[CONTACT_BUFF_SIZE],
        const char *request,
        const ::ssize_t max) {
    bool            flag  = false;
    ::ssize_t       count;

    if (!max)
        return;
    for (count = 0; count != max; count ++) {
        if (request[count] == 0x00)
            flag = true;
        response[count] = (flag ? ' ' : request[count]);
    }
    response[count ++] = (flag ? ' ' : '.');
    response[count] = 0x00;
}


void Contact::clearRead(void) {
    static ::size_t     buff_size = CONTACT_BUFF_SIZE;

    std::size_t         len = CONTACT_BUFF_SIZE;
    char                buff[CONTACT_BUFF_SIZE];
    char                *buff_ptr = buff;

    while (len == CONTACT_BUFF_SIZE) {
        len = ::getline(&buff_ptr, &buff_size, stdin);
    }
}
