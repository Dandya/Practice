#include <stdio.h>
#include <malloc.h>
//----------------------------------------------------------------
int strEQ(char* strFirst,char * strSecond)
{
    int index = 0;
    while(strFirst[index] == strSecond[index])
    {
        if(strFirst[index] == '\0')
        {
            return 1;
        }
        index++;
    }
    if (strFirst[index] == '\n' && strSecond[index] == '\0') // it is penultimate line
    {
        return 1;
    }
    //else
    return 0;
}
//----------------------------------------------------------------
int StrLen(char* string)
{
    if(string == NULL)
    {
        return -1;
    }
    int index = 0;
    while(string[index] != '\0')
    {
        index++;
    }
    return index;
}
//----------------------------------------------------------------
char* concatenationStr(char* strFirst,char* strSecond, int length1, int length2)
{
    char *newStr = realloc(strFirst,length1 + length2 + 1);
    for(int index = 0; index <= length2; index++)
    {
        newStr[index+length1] = strSecond[index];
    }
    return newStr;
}

//----------------------------------------------------------------
char* pushkin(char* text)
{
    char* lines[] = {
        "У лукоморья дуб зеленый,\n",
        "Златая цепь на дубе том:\n",
        "И днем и ночью кот ученый\n",
        "Всё ходит по цепи кругом;\n",
        "Идет направо — песнь заводит,\n",
        "Налево — сказку говорит.\n",
        "\n",
        "Там чудеса: там леший бродит,\n",
        "Русалка на ветвях сидит;\n",
        "Там на неведомых дорожках\n",
        "Следы невиданных зверей;\n",
        "Избушка там на курьих ножках\n",
        "Стоит без окон, без дверей;\n",
        "Там лес и дол видений полны;\n",
        "Там о заре прихлынут волны\n",
        "На брег песчаный и пустой,\n",
        "И тридцать витязей прекрасных;\n",
        "Чредой из вод выходят ясных,\n",
        "И с ними дядька их морской;\n",
        "Там королевич мимоходом\n",
        "Пленяет грозного царя;\n",
        "Там в облаках перед народом\n",
        "Через леса, через моря\n",
        "Колдун несет богатыря;\n",
        "В темнице там царевна тужит,\n",
        "А бурый волк ей верно служит;\n",
        "Там ступа с Бабою Ягой\n",
        "Идет, бредет сама собой;\n",
        "Там царь Кащей над златом чахнет;\n",
        "Там русской дух… там Русью пахнет!\n",
        "И там я был, и мед я пил;\n",
        "У моря видел дуб зеленый;\n",
        "Под ним сидел, и кот ученый\n",
        "Свои мне сказки говорил.\n",
        "Одну я помню: сказку эту\n",
        "Поведаю теперь я свету…\n",
        "\n",
        "Дела давно минувших дней,\n",
        "Преданья старины глубокой.\n",
        "\n",
        "В толпе могучих сыновей,\n",
        "С друзьями, в гриднице высокой\n",
        "Владимир-солнце пировал;\n",
        "Меньшую дочь он выдавал\n",
        "За князя храброго Руслана\n",
        "И мед из тяжкого стакана\n",
        "За их здоровье выпивал.\n",
        "Не скоро ели предки наши,\n",
        "Не скоро двигались кругом\n",
        "Ковши, серебряные чаши\n",
        "С кипящим пивом и вином.\n",
        "Они веселье в сердце лили,\n",
        "Шипела пена по краям,\n",
        "Их важно чашники носили\n",
        "И низко кланялись гостям.\n",
        "\n",
        "Слилися речи в шум невнятный;\n",
        "Жужжит гостей веселый круг;\n",
        "Но вдруг раздался глас приятный\n",
        "И звонких гуслей беглый звук;\n",
        "Все смолкли, слушают Баяна:\n",
        "И славит сладостный певец\n",
        "Людмилу-прелесть, и Руслана,\n",
        "И Лелем свитый им венец.\n",
        "\n",
        "Но, страстью пылкой утомленный,\n",
        "Не ест, не пьет Руслан влюбленный;\n",
        "На друга милого глядит,\n",
        "Вздыхает, сердится, горит\n",
        "И, щипля ус от нетерпенья,\n",
        "Считает каждые мгновенья.\n",
        "В уныньи, с пасмурным челом,\n",
        "За шумным, свадебным столом\n",
        "Сидят три витязя младые;\n",
        "Безмолвны, за ковшом пустым,\n",
        "Забыли кубки круговые,\n",
        "И брашна неприятны им;\n",
        "Не слышат вещего Баяна;\n",
        "Потупили смущенный взгляд:\n",
        "То три соперника Руслана;\n",
        "В душе несчастные таят\n",
        "Любви и ненависти яд.\n",
        "Один — Рогдай, воитель смелый,\n",
        "Мечом раздвинувший пределы\n",
        "Богатых киевских полей;\n",
        "Другой — Фарлаф, крикун надменный,\n",
        "В пирах никем не побежденный,\n",
        "Но воин скромный средь мечей;\n",
        "Последний, полный страстной думы,\n",
        "Младой хазарский хан Ратмир:\n",
        "Все трое бледны и угрюмы,\n",
        "И пир веселый им не в пир.\n",
        "\n",
        "Вот кончен он; встают рядами,\n",
        "Смешались шумными толпами,\n",
        "И все глядят на молодых:\n",
        "Невеста очи опустила,\n",
        "Как будто сердцем приуныла,\n",
        "И светел радостный жених.\n",
        "Но тень объемлет всю природу,\n",
        "Уж близко к полночи глухой;\n",
        "Бояре, задремав от меду,\n",
        "С поклоном убрались домой.\n",
        "Жених в восторге, в упоенье:\n",
        "Ласкает он в воображенье\n",
        "Стыдливой девы красоту;\n",
        "Но с тайным, грустным умиленьем\n",
        "Великий князь благословеньем\n",
        "Дарует юную чету.\n",
        "\n",
        "И вот невесту молодую\n",
        "Ведут на брачную постель;\n",
        "Огни погасли… и ночную\n",
        "Лампаду зажигает Лель.\n",
        "Свершились милые надежды,\n",
        "Любви готовятся дары;\n",
        "Падут ревнивые одежды\n",
        "На цареградские ковры…\n",
        "Вы слышите ль влюбленный шепот,\n",
        "И поцелуев сладкий звук,\n",
        "И прерывающийся ропот\n",
        "Последней робости?.. Супруг\n",
        "Восторги чувствует заране;\n",
        "И вот они настали… Вдруг\n",
        "Гром грянул, свет блеснул в тумане,\n",
        "Лампада гаснет, дым бежит,\n",
        "Кругом всё смерклось, всё дрожит,\n",
        "И замерла душа в Руслане…\n",
        "Всё смолкло. В грозной тишине\n",
        "Раздался дважды голос странный,\n",
        "И кто-то в дымной глубине\n",
        "Взвился чернее мглы туманной…\n",
        "И снова терем пуст и тих;\n",
        "Встает испуганный жених,\n",
        "С лица катится пот остылый;\n",
        "Трепеща, хладною рукой\n",
        "Он вопрошает мрак немой…\n",
        "О горе: нет подруги милой!\n",
        "Хватает воздух он пустой;\n",
        "Людмилы нет во тьме густой,\n",
        "Похищена безвестной силой.\n",
        "\n",
        "Ах, если мученик любви\n",
        "Страдает страстью безнадежно;\n",
        "Хоть грустно жить, друзья мои,\n",
        "Однако жить еще возможно.\n",
        "Но после долгих, долгих лет\n",
        "Обнять влюбленную подругу,\n",
        "Желаний, слез, тоски предмет,\n",
        "И вдруг минутную супругу\n",
        "Навек утратить… о друзья,\n",
        "Конечно лучше б умер я!\n",
        "\n",
        "Однако жив Руслан несчастный.\n",
        "Но что сказал великий князь?\n",
        "Сраженный вдруг молвой ужасной,\n",
        "На зятя гневом распалясь,\n",
        "Его и двор он созывает:\n",
        "«Где, где Людмила?» — вопрошает\n",
        "С ужасным, пламенным челом.\n",
        "Руслан не слышит. «Дети, други!\n",
        "Я помню прежние заслуги:\n",
        "О, сжальтесь вы над стариком!\n",
        "Скажите, кто из вас согласен\n",
        "Скакать за дочерью моей?\n",
        "Чей подвиг будет не напрасен,\n",
        "Тому — терзайся, плачь, злодей!\n",
        "Не мог сберечь жены своей! —\n",
        "Тому я дам ее в супруги\n",
        "С полцарством прадедов моих.\n",
        "Кто ж вызовется, дети, други?..»\n",
        "«Я!» — молвил горестный жених.\n",
        "«Я! я!» — воскликнули с Рогдаем\n",
        "Фарлаф и радостный Ратмир:\n",
        "«Сейчас коней своих седлаем;\n",
        "Мы рады весь изъездить мир.\n",
        "Отец наш, не продлим разлуки;\n",
        "Не бойся: едем за княжной».\n",
        "И с благодарностью немой\n",
        "В слезах к ним простирает руки\n",
        "Старик, измученный тоской.\n",
        "\n",
        "Все четверо выходят вместе;\n",
        "Руслан уныньем как убит;\n",
        "Мысль о потерянной невесте\n",
        "Его терзает и мертвит.\n",
        "Садятся на коней ретивых;\n",
        "Вдоль берегов Днепра счастливых\n",
        "Летят в клубящейся пыли;\n",
        "Уже скрываются вдали;\n",
        "Уж всадников не видно боле…\n",
        "Но долго всё еще глядит\n",
        "Великий князь в пустое поле\n",
        "И думой им вослед летит.\n",
        "\n",
        "Руслан томился молчаливо,\n",
        "И смысл и память потеряв.\n",
        "Через плечо глядя спесиво\n",
        "И важно подбочась, Фарлаф,\n",
        "Надувшись, ехал за Русланом.\n",
        "Он говорит: «Насилу я\n",
        "На волю вырвался, друзья!\n",
        "Ну, скоро ль встречусь с великаном?\n",
        "Уж то-то крови будет течь,\n",
        "Уж то-то жертв любви ревнивой!\n",
        "Повеселись, мой верный меч,\n",
        "Повеселись, мой конь ретивый!»\n"
    };
    if(text == NULL)
    {
        return concatenationStr(NULL, lines[0], 0, 46);
    }
    int index = 0;
    int indexLastLF = -1; //It need for first line
    //search last line in text by means of last "\n" before last line
    while(text[index] != '\0')
    {
        if(text[index] == '\n' && text[index+1] != '\0')
        {
            indexLastLF = index;
        }
        index++;
    }
    int isPenultimateLine = 0;
    if(index - indexLastLF == 2) // then last line is "\n" and we need penultimate line
    {
        isPenultimateLine = 1;
        do
        {
            indexLastLF--;
        }
        while(text[indexLastLF] != '\n');
    }
    //search next line in @lines
    for(int i = 0; i < 207; i++)
    {
        if(strEQ(text+indexLastLF+1, lines[i]))
        {
            return concatenationStr(text, lines[isPenultimateLine ? i+2 : i+1], index, StrLen(lines[isPenultimateLine ? i+2 : i+1])); 
        }
    }
    printf("Строка: %sНе найдена в тексте!",text+indexLastLF+1 )
    return NULL;
}
