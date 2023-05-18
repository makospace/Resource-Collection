-- 编写一个SQL查询来报告 Employee 表中第 n 高的工资。如果没有第 n 个最高工资，查询应该报告为 null 
CREATE FUNCTION getNthHighestSalary(@N INT) RETURNS INT AS
BEGIN
    RETURN (
        /* Write your T-SQL query statement below. */
		-- 选出第N高的工资，如果没有第N个最高工资，查询应该报告为null
		SELECT TOP 1 Salary
		FROM Employee
		ORDER BY Salary DESC
		OFFSET @N-1 ROWS
		
    );
END