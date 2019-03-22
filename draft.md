
## code smells

first edition:

- [x]: duplacated code
- [n]: long method
- [x]: large class
- [x]: long parameter list
- [x]: divergent change
- [x]: shotgun surgery
- [x]: feature envy
- [x]: data clumps
- [x]: primitive obsession
- [n]: switch statement
- [ ]: parallel inheriance hierarchies
- [n]: lazy class
- [x]: speculative generality
- [x]: temporary field
- [x]: message chains
- [x]: middle man
- [ ]: inappropriate intimacy
- [x]: alternative classes ith different interfaces
- [ ]: incomplete library class
- [x]: data class
- [x]: refused bequest
- [x]: comments



second edition:

- [ ]: mysterious name
- [x]: duplicated code
- [n]: long function
- [x]: long parameter list
- [ ]: global data
- [ ]: mutable data
- [x]: divergent change
- [x]: shotgun surgery
- [x]: feature envy
- [x]: data clumps
- [x]: primitive obsession
- [n]: repleated switch
- [ ]: loops
- [n]: lazy element
- [x]: speculative generality
- [x]: temporary field
- [x]: message chains
- [x]: middle man
- [ ]: insider trading
- [x]: large class
- [x]: alternative classes with different interfaces
- [x]: data class
- [x]: refused bequest
- [x]: comments

|**第一版**|**第二版**|**变化概要**|
|:-:|:-:|-|
|✗|神秘命名<br>`Mysterious Name`|新版增加，突出了好的命名对于代码的重要性|
|重复代码<br>`Duplicataed Code`|重复代码<br>`Duplicataed Code`|新版删除了对毫不相干的类中出现重复的描述，避免不合时宜的提取非本质重复|
|过长函数<br>`Long Method`|过长函数<br>`Long Function`|基本未变|
|过长参数列表<br>`Long Parameter List`|过长参数列表<br>`Long Parameter List`|新版提供了更多的新的重构解决方案|
|✗|全局数据<br>`Global Data`|新版突出了全局数据对代码耦合性的恶劣影响|
|✗|可变数据<br>`Mutable Data`|新版突出了适宜的不可变性对代码可维护性上的优势|
|发散式变化<br>`Divergent Change`|发散式变化<br>`Divergent Change`|新版提供了更多应对发散式变化的重构方案|
|霰弹式修改<br>`Shotgun Surgery`|霰弹式修改<br>`Shotgun Surgery`|新版提供了更多应对霰弹式修改的重构方案|
|依恋情结<br>`Feature Envy`|依恋情结<br>`Feature Envy`|新版对封装单元的表述不再仅仅针对类，扩展到函数和模块|
|数据泥团<br>`Data Clumps`|数据泥团<br>`Data Clumps`|基本未变|
|基本类型偏执<br>`Primitive Obsession`|基本类型偏执<br>`Primitive Obsession`|新版增加了`类字符类型变量`的危害，并简化了表达方式|
|Switch表达式<br>`Switch Statement`|重复的Switch<br>`Repleated Switch`|新版承认之前“矫枉过正”，重构的核心是要消除**重复**的switch|
|✗|循环语句<br>`Loops`|凸显了在函数式下，循环有了更多的更具语义性的表达方式|
|平行继承体系<br>`Parallel Inheritance Hierarchies`|✗|平行继承体系其实是散弹式修改的特殊形式。为了不再突出面向对象，新版删去|
|冗赘类<br>`Lazy Class`|冗赘的元素<br>`Lazy Element`|新版中体现了冗余的未必只是类，可能是函数、模块等|
|夸夸其谈通用性<br>`Speculative Generality`|夸夸其谈通用性<br>`Speculative Generality`|基本未变|
|临时字段<br>`Temporary Field`|临时字段<br>`Temporary Field`|删除为了特殊算法引入临时字段的情况|
|过长的消息链<br>`Message Chains`|过长的消息链<br>`Message Chains`|基本未变|
|中间人<br>`Middle Man`|中间人<br>`Middle Man`|基本未变|
|狎昵关系<br>`Inappropriate Intimacy`|内幕交易<br>`Insider Trading`|新版中不再仅限于类之间的不恰当耦合，将描述范围扩大到模块|
|过大的类<br>`Large Class`|过大的类<br>`Large Class`|旧版中描述的`GUI大类`已经有些过时了，所以删除了|
|异曲同工的类<br>`Alternative Classes with Different Interfaces`|异曲同工的类<br>`Alternative Classes with Different Interfaces`|新版对所谓类的"异曲同工"解释的更加清晰|
|不完美的类库<br>`Incomplete Library Class`|✗|类库属于可扩展不可修改的代码，新版中把对类库的坏味道辨别和重构删掉了|
|纯数据类<br>`Data Class`|纯数据类<br>`Data Class`|新版提出了例外情况：当纯数据类不可修改且仅用于传递信息时|
|被拒绝的遗赠<br>`Refused Bequest`|被拒绝的遗赠<br>`Refused Bequest`|基本未变|
|注释<br>`Comments`|注释<br>`Comments`|基本未变|

## refactoring steps

first edition

- 重新组织函数
    - 提炼函数 Extract Method
    - 内联函数 Inline Method

- 在对象之间搬移特性
- 重新组织数据
- 简化条件表达式
- 简化函数调用
- 处理概括关系

second edition

- 第一组重构
    - 提炼函数 Extract Function
        - “在我看来，一个函数超过6行，就开始散发臭味”
        - 反向手法的价值，可撤销
        - 语言特性的利用：函数嵌套
    - 内联函数 Inline Function
        - 增加代码示例
    - 提炼变量 Extract Variable
        - 新增
        
- 封装
- 搬移特性
- 重新组织数据
- 简化条件逻辑
- 重构API
- 处理继承关系

变化：
- 组织结构
- 曾用名、反向重构
- 插图
