// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// Java from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


package org.usfirst.frc2465.Robot.commands;

import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.command.CommandGroup;
import org.usfirst.frc2465.Robot.Robot;
import org.usfirst.frc2465.Robot.RobotPreferences;
import org.usfirst.frc2465.Robot.subsystems.Kicker;
import org.usfirst.frc2465.Robot.subsystems.Tensioner;

/**
 *
 */
public class  DefaultTension extends CommandGroup {

    public DefaultTension() {
	addSequential(new SetTension(
                2.4,true));
    }
}
