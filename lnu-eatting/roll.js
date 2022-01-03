var foods = new Map();

foods.set("外卖", [
"魔饭堂","老汤拉面","咖喱饭","河南烩面","简单味道"
,"烤肉饭","牛肉汤","三杯鸡","味恋客","一碗好饭"
,"萌锅蒸饭","蒸饺","淮南汤饭", "今日特价"
]);

foods.set("食堂", ["友园","桃李园","三四"]);

foods.set("早餐", ["小笼包"]);

foods.set("校外", ["烤鸭", "水果捞", "烤鸡", "比萨"])

function Roll() {
    result = document.getElementById("result");

    select = document.getElementById("select");
    selectText = select.options[select.selectedIndex].text;

    selectFoods = foods.get(selectText);
    if (selectText == "全部") {
        selectFoods = foods.get("外卖").concat(foods.get("食堂"));
    }

    randNum = Math.floor(Math.random() * selectFoods.length);
    result.innerHTML = selectFoods[randNum];

    button = document.getElementById("button");
    button.innerHTML = "重来";
}