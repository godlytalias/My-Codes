/**
 * A trigger-driven function that sends out calendar invitations and a
 * personalized Google Docs itinerary after a user responds to the form.
 *
 * @param {Object} e The event parameter for form submission to a spreadsheet;
 *     see https://developers.google.com/apps-script/understanding_events
 */
function onFormSubmit(e) {

  var SHEETNAME = 'editedresponse';
  var AGEGROUP = [10, 15, 20, 25, 30];  //upper age limit of each age group (inclusive)
  var TEACHERCOUNT = [5, 5, 5, 5, 5];   //Number of teachers available for each agegroup
    
  var age = e.namedValues['Age'];
  var name = e.namedValues['Name'];
  Logger.log("form submitted by " + name + " age : " + age);
  if (age == '' || name == '') return;
 
  var ageGroupPos = 0;
  var i;
  for (;age < AGEGROUP[ageGroupPos]; ageGroupPos++);
  Logger.log("Age group pos : " + ageGroupPos);

  var ageGroupRow = 2;
  while(ageGroupRow < SpreadsheetApp.getActive().getSheetByName(SHEETNAME).getLastRow())
  {
     var rowValue = SpreadsheetApp.getActive().getSheetByName(SHEETNAME).getRange(ageGroupRow, 1).getValue();
     if (rowValue != '' && age <= AGEGROUP[ageGroupRow - 2]) break;
     ageGroupRow++;
  }
  Logger.log("group row " + ageGroupRow);
  var ageGroupStrength = 0;
  if (SpreadsheetApp.getActive().getSheetByName(SHEETNAME).getRange(ageGroupRow, 2).getValue().length == 0)
    ageGroupStrength = 0;
  else
  {
    ageGroupStrength = 1;
    for (i = ageGroupRow + 1; i < SpreadsheetApp.getActive().getSheetByName(SHEETNAME).getLastRow(); i++)
    {
      if (SpreadsheetApp.getActive().getSheetByName(SHEETNAME).getRange(i, 1).getValue() != '') break;
      else ageGroupStrength++;
    }
  }
  
  var classRow = 0;
  Logger.log("age group strength " + ageGroupStrength);
  
  if (ageGroupStrength < TEACHERCOUNT[ageGroupPos])
  {
    Logger.log("Initializing Part");
    if (SpreadsheetApp.getActive().getSheetByName(SHEETNAME).getRange(ageGroupRow, 2).getValue().length == 0)
    {
      SpreadsheetApp.getActive().getSheetByName(SHEETNAME).getRange(ageGroupRow, 2).setValue('Teacher1');
      SpreadsheetApp.getActive().getSheetByName(SHEETNAME).getRange(ageGroupRow + ageGroupStrength, 3).setValue(name);
      SpreadsheetApp.getActive().getSheetByName(SHEETNAME).getRange(ageGroupRow + ageGroupStrength, 4).setValue(age);
    }
    else
    {
      SpreadsheetApp.getActive().getSheetByName(SHEETNAME).insertRowAfter(ageGroupRow + ageGroupStrength - 1);
      SpreadsheetApp.getActive().getSheetByName(SHEETNAME).getRange(ageGroupRow, 1, ageGroupStrength + 1).merge().setHorizontalAlignment("center").setVerticalAlignment("middle");
      SpreadsheetApp.getActive().getSheetByName(SHEETNAME).getRange(ageGroupRow + ageGroupStrength, 2).setValue('Teacher' + (ageGroupStrength + 1));
      SpreadsheetApp.getActive().getSheetByName(SHEETNAME).getRange(ageGroupRow + ageGroupStrength, 3).setValue(name);
      SpreadsheetApp.getActive().getSheetByName(SHEETNAME).getRange(ageGroupRow + ageGroupStrength, 4).setValue(age);
    }
    
  }
  else
  {
    Logger.log("Student Filling");
    var teacherCount = TEACHERCOUNT[ageGroupPos];
    var nextTeacher = (ageGroupStrength % teacherCount) + 1;
    var classStrength = Math.floor(ageGroupStrength / teacherCount) + 1;
    var TeacherPos = classStrength * (nextTeacher - 1);
    var nextPos = TeacherPos + classStrength - 1;
    Logger.log("Teacher Pos : " + TeacherPos + " Class Strength : " + classStrength + " Next Teacher : " + nextTeacher);
    SpreadsheetApp.getActive().getSheetByName(SHEETNAME).insertRowAfter(ageGroupRow + nextPos - 1);
    SpreadsheetApp.getActive().getSheetByName(SHEETNAME).getRange(ageGroupRow + TeacherPos, 2, classStrength).merge().setHorizontalAlignment("center").setVerticalAlignment("middle");
    SpreadsheetApp.getActive().getSheetByName(SHEETNAME).getRange(ageGroupRow, 1, ageGroupStrength + 1).merge().setHorizontalAlignment("center").setVerticalAlignment("middle");
    SpreadsheetApp.getActive().getSheetByName(SHEETNAME).getRange(ageGroupRow + nextPos, 3).setValue(name);
    SpreadsheetApp.getActive().getSheetByName(SHEETNAME).getRange(ageGroupRow + nextPos, 4).setValue(age);
  }
}
