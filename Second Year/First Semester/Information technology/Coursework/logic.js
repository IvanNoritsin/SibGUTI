function renderTable(container, thead, trows, id)
{
    let table = document.getElementById(container);
    if(table != null)
    {
        let htmlTable = "<table id='dat'>"; 
        htmlTable += "<thead>"; 
            htmlTable += "<tr>"; 
                htmlTable += "<td>class</td>"
                let rHead = trows[thead[0]][id]['distribution'];
        
                for (const [key, value] of Object.entries(rHead)) {
                    console.log(key, value);
                    if(key == 'undefined') continue; 
                    htmlTable += "<td>count_" + key + "</td>";
                    htmlTable += "<td>percent_" + key + "</td>"
                }
                
            htmlTable += "</tr>"
        htmlTable += "</thead>"; 
        htmlTable += "<tbody>"; 
            console.log(htmlTable)
            thead.forEach(function(element, idx) {
                htmlTable += "<tr>";
                htmlTable += "<td>" + element + "</td>"

                let h = Object.keys(trows[element][id]['distribution'])
                console.log(h)
                h.forEach(element2 => {
                    console.log("DSDSDSD", trows[element][id]['distribution'][element2] );
                    if ( typeof trows[element][id]['distribution'][element2]['count'] != "undefined" ) {
                        //console.log("YEEES", trows[element][id]['distribution'][element2]);
                        htmlTable += "<td>" + trows[element][id]['distribution'][element2]['count'] + "</td>"
                        htmlTable += "<td>" + trows[element][id]['distribution'][element2]['count'] + "</td>"
                    }
                })
                htmlTable += "</tr>";
            })
        htmlTable += "</tbody>"
    htmlTable += "</table>";    

    table.innerHTML = htmlTable;
    }
}

window.onload = function()
{
    let fileIO = document.getElementById('fileInput')
    if(fileIO != null)
    {
        fileIO.addEventListener('change', function(event) {
            var files = event.target.files;
            for (var i = 0; i < files.length; i++) {
                var file = files[i];
                var reader = new FileReader();
                reader.onload = function(e) {
                    var contents = e.target.result;
                    var dataArray = [];
    
                    if (file.name.endsWith('.csv')) {
                        dataArray = parseCSV(contents);
                        localStorage.setItem('fileType', 'text/csv');
                    } else if (file.name.endsWith('.xlsx')) {
                        dataArray = parseXLSX(contents);
                        localStorage.setItem('fileType', 'text/xlsx');
                    } else if (file.name.endsWith('.txt')) {
                        dataArray = parseTXT(contents);
                        localStorage.setItem('fileType', 'text/txt');
                    }
                    console.log(dataArray);
    
                    cacheData(dataArray);
                };
                reader.readAsText(file, "cp1251");
            }
        });   
    }
     

    let statisticBtn = document.getElementById('statsRefresh');
    if (statisticBtn != null) {
        statisticBtn.addEventListener('click', function(e) {
            // Преобразование исходного массива в объекты JavaScript
            let data = getCacheData()
            var students = data.map(item => ({
                name: item.name,
                class: item.class,
                grades: {
                    mathemathics: item.mathemathics,
                    physics: item.physics,
                    informatics: item.inforatics,
                    literature: item['literature '], 
                    music: item.music
                }
            }));

            // Создание нового массива со статистикой для каждого класса и предмета
            var classSubjectStats = {};
            students.forEach(student => {
                if (!classSubjectStats[student.class]) {
                classSubjectStats[student.class] = {};
                }
                for (var subject in student.grades) {
                if (!classSubjectStats[student.class][subject]) {
                    classSubjectStats[student.class][subject] = [];
                }
                classSubjectStats[student.class][subject].push(student.grades[subject]);
                }
            });
            
            for (var classNum in classSubjectStats) {
                for (var subject in classSubjectStats[classNum]) {
                classSubjectStats[classNum][subject] = calculateStats(classSubjectStats[classNum][subject]);
                }
            }
            
            // Создание нового массива со статистикой для всех учеников по каждому предмету
            var allStudentsStats = {};
            for (var subject in students[0].grades) {
                allStudentsStats[subject] = calculateStats(students.map(student => student.grades[subject]));
            }

            let thead = Object.keys(classSubjectStats)
            thead.splice(3, 1);

            console.log(classSubjectStats, allStudentsStats)

            renderTable('group-math-stats', thead, classSubjectStats, "mathemathics");
            renderTable('group-info-stats', thead, classSubjectStats, "informatics");
            renderTable('group-phys-stats', thead, classSubjectStats, "physics");
            renderTable('group-lite-stats', thead, classSubjectStats, "literature");
            renderTable('group-musi-stats', thead, classSubjectStats, "music");


        })
    }
}

  
  // Функция для вычисления статистики по оценкам
  function calculateStats(data) {
    var sum = data.reduce((acc, val) => acc + val, 0);
    var count = data.length;
    console.log('SUM', sum, "COUNT", count);
    var average = sum / count;
    data.sort((a, b) => a - b);
    var median = count % 2 === 0 ? (data[count / 2 - 1] + data[count / 2]) / 2 : data[Math.floor(count / 2)];
    
    var stats = {
      average: average,
      median: median,
      count: count,
      distribution: {}
    };
  
    data.forEach(grade => {
      if (!stats.distribution[grade]) {
        stats.distribution[grade] = 1;
      } else {
        stats.distribution[grade]++;
      }
    });
  
    for (var grade in stats.distribution) {
      stats.distribution[grade] = {
        count: stats.distribution[grade],
        percentage: (stats.distribution[grade] / count) * 100
      };
    }
  
    return stats;
  }
  

function parseCSV(csvContent) {
    var lines = csvContent.split('\r');
    var result = [];
    var headers = lines[0].split(';');
    for (var i = 1; i < lines.length; i++) {
        var obj = {};
        var currentLine = lines[i].split(';');
        for (var j = 0; j < headers.length; j++) {
            obj[headers[j]] = currentLine[j];
        }
        result.push(obj);
    }
    return result;
}
  
function parseXLSX(xlsxContent) {
    var workbook = XLSX.read(xlsxContent, {type: 'binary'});
    var sheetName = workbook.SheetNames[0];
    var sheet = workbook.Sheets[sheetName];
    var result = XLSX.utils.sheet_to_json(sheet, {header: 1});
    return result;
}
  
function parseTXT(txtContent) {
    var lines = txtContent.split('\n');
    var result = [];
    for (var i = 0; i < lines.length; i++) {
      result.push(lines[i].trim());
    }
    return result;
}

function cacheData(dataArray) {
    localStorage.setItem('dataArray', JSON.stringify(dataArray));
}

function ClearCacheData() {
    localStorage.setItem('dataArray', null);
}

function getCacheData() {
    return JSON.parse(localStorage.getItem("dataArray"))
}

function makeTable(thead, trows, isEditable) 
{ 
    let table = document.getElementById('table-container');

    let num = 1; 

    let htmlTable = "<table id='dat'>"; 
        htmlTable += "<thead>"; 
            htmlTable += "<tr>"; 
                htmlTable += "<td>N</td>"
                thead.forEach(element => {
                    htmlTable += "<td>" + element + "</td>"
                });
            htmlTable += "</tr>"
        htmlTable += "</thead>"; 
        htmlTable += "<tbody>"; 
            trows.forEach(element => {
                if ( typeof element[thead[1]] != 'undefined' ) {
                    htmlTable += '<tr data-row="' + (num - 1) + '">';
                        htmlTable += "<td>" + num + "</td>"; 
                        if(isEditable) { 
                            htmlTable += "<td><input data-row='" + (num - 1) + "' type='text' class='name' value='" + element[thead[0]] + "'></td>"; 
                            htmlTable += "<td><input data-row='" + (num - 1) + "' type='text' class='class' value='" + element[thead[1]] + "'></td>"; 
                            htmlTable += "<td><input data-row='" + (num - 1) + "' type='number' class='info' value='" + element[thead[2]] + "' min=0 max=5></td>"; 
                            htmlTable += "<td><input data-row='" + (num - 1) + "' type='number' class='phys' value='" + element[thead[3]] + "' min=0 max=5></td>"; 
                            htmlTable += "<td><input data-row='" + (num - 1) + "' type='number' class='math' value='" + element[thead[4]] + "' min=0 max=5></td>"; 
                            htmlTable += "<td><input data-row='" + (num - 1) + "' type='number' class='lite' value='" + element[thead[5]] + "' min=0 max=5></td>"; 
                            htmlTable += "<td><input data-row='" + (num - 1) + "' type='number' class='musi' value='" + element[thead[6]] + "' min=0 max=5></td>"; 
                        }
                        else {
                            htmlTable += "<td>" + element[thead[0]] + "</td>";
                            htmlTable += "<td>" + element[thead[1]] + "</td>";
                            htmlTable += "<td>" + element[thead[2]] + "</td>";
                            htmlTable += "<td>" + element[thead[3]] + "</td>";
                            htmlTable += "<td>" + element[thead[4]] + "</td>";
                            htmlTable += "<td>" + element[thead[5]] + "</td>";
                            htmlTable += "<td>" + element[thead[6]] + "</td>";
                        }
                       
                        htmlTable += "<td>";
                            htmlTable += '<button class="deleteBtn" data-row="'+ (num - 1) +'" type="button">Удалить</button>';
                        htmlTable += "</td>"; 
                    htmlTable += "</tr>";

                    num += 1;
                }
            })
        htmlTable += "</tbody>"
    htmlTable += "</table>";    

    table.innerHTML = htmlTable
    
    var deleteButtons = document.querySelectorAll('tr button[class="deleteBtn"]');

    deleteButtons.forEach(function(button) {
        button.addEventListener('click', function(e) {
            var row = this.closest('tr');
            let idx = parseInt(e.target.dataset.row);

            let data = getCacheData(); 
            
            data.splice(idx, 1);

            cacheData(data)

            row.remove();
        });
    });

    let IOInputsCells = document.querySelectorAll('input[class="info"],input[class="math"],input[class="phys"],input[class="lite"],input[class="musi"]'); 

    IOInputsCells.forEach((element) => {
        element.addEventListener("change", (e) => {
            console.log(e.target.value, e.target.dataset.row, e.target.class);

            let dataArray = getCacheData();
            if(e.target.className  == "math")
            {
                dataArray[e.target.dataset.row]['mathemathics'] = e.target.value;
            }
            if(e.target.className  == "info")
            {
                dataArray[e.target.dataset.row]['informatics'] = e.target.value;
            }
            if(e.target.className  == "phys")
            {
                dataArray[e.target.dataset.row]['physics'] = e.target.value;
            }
            if(e.target.className  == "lite")
            {
                dataArray[e.target.dataset.row]['literature '] = e.target.value;
            }
            if(e.target.className  == "musi")
            {
                dataArray[e.target.dataset.row]['music'] = e.target.value;
            }
            cacheData(dataArray);
        });
    })
}

function drawTable() {
    console.log('Draw func');

    let table_new_row = document.getElementById('table-new-row');
    if (table_new_row != null) 
    { 
        let htmlTable = "<table style='float:left'>";
            htmlTable += "<thead>"; 
                htmlTable += "<tr>"; 
                    ['name', 'class', 'informatic', 'physics', 'mathematics', 'literature', 'music'].forEach(element => {
                        htmlTable += "<td colspan='10px'>" + element + "</td>"
                    });
                htmlTable += "</tr>"
            htmlTable += "</thead>"; 
            htmlTable += "<tbody><tr>"; 
                htmlTable += '<td colspan="10px"><input id="nname"></td>';
                htmlTable += '<td colspan="10px"><input id="nclass"></td>';
                htmlTable += '<td colspan="10px"><input id="ninfo" type="number" min=0 max=5></td>';
                htmlTable += '<td colspan="10px"><input id="nphys" type="number" min=0 max=5></td>';
                htmlTable += '<td colspan="10px"><input id="nmath" type="number" min=0 max=5></td>';
                htmlTable += '<td colspan="10px"><input id="nlite" type="number" min=0 max=5></td>';
                htmlTable += '<td colspan="10px"><input id="nmusi" type="number" min=0 max=5></td>';
                htmlTable += '<td><button id="newBtn" type="button">Добавить</button></td>';
            htmlTable += "</tr></tbody>"; 
        htmlTable += "</table>"; 

        table_new_row.innerHTML = htmlTable;
    }

    let add_button = document.getElementById('newBtn');
    if (add_button != null)
    {
        add_button.addEventListener('click', function() {
            let tab = document.getElementById('dat'); 

            let last_row;

            if (tab != null)
                last_row = tab.rows[ tab.rows.length - 1 ];

            let _name = document.getElementById('nname').value;
            let _class = document.getElementById('nclass').value;
            let _info = document.getElementById('ninfo').value;
            let _phys = document.getElementById('nphys').value;
            let _math = document.getElementById('nmath').value;
            let _lite = document.getElementById('nlite').value;
            let _musi = document.getElementById('nmusi').value; 

            let _id;
            
            if (_name != "" && _class != "" && 
                (_info > 0 && _info <= 5) &&
                (_phys > 0 && _phys <= 5) &&
                (_math > 0 && _math <= 5) &&
                (_lite > 0 && _lite <= 5) &&
                (_musi > 0 && _musi <= 5) 
            )
            {
                if (last_row == null)
                {
                    _id = 1; 
                    let table = document.getElementById('table-container');
                    let htmlTable = "<table id='dat'>"; 
                        htmlTable += "<thead>"; 
                            htmlTable += "<tr>"; 
                                htmlTable += "<td>N</td>"
                                let heeadss = ['name','class', 'informatics', 'physics', 'mathemathics', 'literature', 'music'];
                                heeadss.forEach(element => {
                                    htmlTable += "<td>" + element + "</td>"
                                });
                            htmlTable += "</tr>"
                        htmlTable += "</thead>"; 
                        htmlTable += "<tbody>"; 
                            htmlTable += '<tr data-row="' + (_id - 1) + '">';
                                htmlTable += "<td>" + _id + "</td>"; 
                                    htmlTable += "<td><input data-row='" + (_id - 1) + "' type='text' class='name' value='" + _name + "'></td>"; 
                                    htmlTable += "<td><input data-row='" + (_id - 1) + "' type='text' class='class' value='" + _class + "'></td>"; 
                                    htmlTable += "<td><input data-row='" + (_id - 1) + "' type='number' class='info' value='" + _info + "' min=0 max=5></td>"; 
                                    htmlTable += "<td><input data-row='" + (_id - 1) + "' type='number' class='phys' value='" + _phys + "' min=0 max=5></td>"; 
                                    htmlTable += "<td><input data-row='" + (_id - 1) + "' type='number' class='math' value='" + _math + "' min=0 max=5></td>"; 
                                    htmlTable += "<td><input data-row='" + (_id - 1) + "' type='number' class='lite' value='" + _lite + "' min=0 max=5></td>"; 
                                    htmlTable += "<td><input data-row='" + (_id - 1) + "' type='number' class='musi' value='" + _musi + "' min=0 max=5></td>"; 
                                htmlTable += "<td>";
                                    htmlTable += '<button class="deleteBtn" data-row="'+ (_id - 1) +'" type="button">Удалить</button>';
                                htmlTable += "</td>"; 
                            htmlTable += "</tr>";
                        htmlTable += "</tbody>"
                    htmlTable += "</table>";
                    table.innerHTML = htmlTable;
                    
                }
                    
                else 
                {
                    _id = parseInt(last_row.dataset.row) + 2;

                    var row = tab.insertRow();

                    row.dataset.row = _id - 1;

                    var td0 = row.insertCell(0).innerHTML = _id;
                    var td1 = row.insertCell(1).innerHTML = "<input data-row='" + (_id - 1) + "' type='text' class='name' value='" + _name + "'>";
                    var td2 = row.insertCell(2).innerHTML = "<input data-row='" + (_id - 1) + "' type='text' class='class' value='" + _class + "'>";;
                    var td3 = row.insertCell(3).innerHTML = "<input data-row='" + (_id - 1) + "' type='number' class='info' value='" + _info + "' min=0 max=5>";;
                    var td4 = row.insertCell(4).innerHTML = "<input data-row='" + (_id - 1) + "' type='number' class='phys' value='" + _phys + "' min=0 max=5>";;
                    var td5 = row.insertCell(5).innerHTML = "<input data-row='" + (_id - 1) + "' type='number' class='math' value='" + _math + "' min=0 max=5>";;
                    var td6 = row.insertCell(6).innerHTML = "<input data-row='" + (_id - 1) + "' type='number' class='lite' value='" + _lite + "' min=0 max=5>";;
                    var td7 = row.insertCell(7).innerHTML = "<input data-row='" + (_id - 1) + "' type='number' class='musi' value='" + _musi + "' min=0 max=5>";;
                    var td8 = row.insertCell(8).innerHTML = '<button class="deleteBtn" data-row="'+ (_id - 1) +'" type="button">Удалить</button>';
                }

                let newrow = {
                    "name":_name, 
                    "class":_class,
                    "informatics":_info, 
                    "physics":_phys,
                    "mathemathics":_math, 
                    "literature ":_lite, 
                    "music":_musi
                };

                if(typeof getCacheData() == null){
                    cacheData([newrow]);
                }
                else 
                { 
                    let dataArray = getCacheData();

                    dataArray.push(newrow);

                    cacheData(dataArray);
                }
                console.log("NewRow", newrow);
            } else { alert("Некорректные данные при добавлении новой строки"); }
        });
    }

    let dataArray = getCacheData();
    
    if ( typeof dataArray == null ) return; 

    let thead = Object.keys(dataArray[0])

    makeTable(thead, dataArray, true)
}
