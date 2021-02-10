var addon = require('bindings')('addon');

addon.passArray(["abc", 123], (error1, printer) => {
  if (error) throw error1;

  printer.printArray((error2, array) => {
    if (error2) throw error2;

    console.log(array);
  });
});