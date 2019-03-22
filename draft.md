
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


|**第一版**|**第二版**|**变化**|
|--|--|--|
||神秘命名<br>Mysterious Name|突出了好的命名对于代码的重要性|
|重复代码<br>Duplicataed Code|重复代码<br>Duplicataed Code|新版对此进行了简化，避免提取非本质重复|
|过长函数<br>Long Method|过长函数<br>Long Function||
|过长参数列表<br>Long Parameter List|过长参数列表<br>Long Parameter List|新的解决方案：部分应用函数|
||全局数据<br>Global Data|突出了全局数据对代码耦合性的恶劣影响|
||可变数据<br>Mutable Data|突出了不可变性对代码可维护性上的优势|
|发散式变化<br>Divergent Change|发散式变化<br>Divergent Change|提供了应对发散式变化的重构手法|
|霰弹式修改<br>Shotgun Surgery|霰弹式修改<br>Shotgun Surgery|提供了更多对应霰弹式修改的重构手法|
|依恋情结<br>Feature Envy|依恋情结<br>Feature Envy|对封装单元的表述不再仅仅针对类，扩展到函数和模块|
|数据泥团<br>Data Clumps|数据泥团<br>Data Clumps|没有变化|
|基本类型偏执<br>Primitive Obsession|基本类型偏执<br>Primitive Obsession|介绍了类字符变量，简化了描述|
|Switch表达式<br>Switch Statement|重复的Switch<br>Repleated Switch|承认之前矫枉过正，核心是要消除重复的switch|
||循环语句<br>Loops|新的矫枉过正；由于函数式的出现，循环有了更多的更具语义性的表达方式，例如管道或者流式操作|
|平行继承体系<br>Parallel Inheritance Hierarchies||平行继承体系其实是散弹式修改的特殊形式，不再突出面向对象，新版删去|
|冗赘类<br>Lazy Class|冗赘的元素<br>Lazy Element|新版扩展了内涵，冗余的未必只是类，可能是函数、模块等任何当初想着能被复用的代码单元|
|夸夸其谈通用性<br>Speculative Generality|夸夸其谈通用性<br>Speculative Generality|基本未变|
|临时字段<br>Temporary Field|临时字段<br>Temporary Field|删除了由于特殊算法引入临时字段的情况描述|
|过长的消息链<br>Message Chains|过长的消息链<br>Message Chains|没有变|
|中间人<br>Middle Man|中间人<br>Middle Man|没有变|
|狎昵关系<br>Inappropriate Intimacy|内部交易<br>Insider Trading|过度耦合的代码单元不仅仅局限于类，新版使用了模块这个更普遍的称呼|
|过大的类<br>Large Class|过大的类<br>Large Class|旧版中描述的GUI大类已经有些过时了，所以删除了|
|异曲同工的类<br><br>Alternative Classes with Different Interfaces|异曲同工的类<br><br>Alternative Classes with Different Interfaces|对所谓类的异曲同工解释的更加清晰|
|不完美的类库<br>Incomplete Library Class||类库属于只可扩展不可修改的代码，新版对类库的换味道辨别和重构删掉了|
|纯数据类<br>Data Class|纯数据类<br>Data Class|提出了例外情况：那就是不可修改的用于传递信息纯数据类，例如函数返回值或者阶段传递数据|
|被拒绝的遗赠<br>Refused Bequest|被拒绝的遗赠<br>Refused Bequest|基本未变|
|注释<br>Comments|注释<br>Comments|没有变化|

