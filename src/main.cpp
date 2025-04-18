#include <FEH.h>
#include <Arduino.h>

void waitUntilTouch()
{
    int left;
    int right;

    while (!LCD.Touch(&left, &right))
    {
    }

    while (LCD.Touch(&left, &right))
    {
    }
}

void write(String msg)
{
    LCD.WriteLine(msg);
    Serial.println(msg);
}

void ERCMain()
{
    AnalogInputPin cdsCell(FEHIO::Pin8);

    // No light
    write("Prepare for no light");
    waitUntilTouch();
    write("No light value: " + String(cdsCell.Value()));

    // Red light
    LCD.Clear();
    write("\nPrepare for red light");
    waitUntilTouch();
    write("red light value: " + String(cdsCell.Value()));

    // Blue light
    LCD.Clear();
    write("\nPrepare for blue light");
    waitUntilTouch();
    write("blue light value: " + String(cdsCell.Value()));
}