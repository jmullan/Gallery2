
-- Install install our custom aggregate function.

CREATE AGGREGATE BIT_OR (
    basetype = bit,
    sfunc = bitor,
    stype = bit
)
