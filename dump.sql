--
-- PostgreSQL database dump
--

-- Dumped from database version 10.10
-- Dumped by pg_dump version 10.10

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: registro; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.registro (
    id integer NOT NULL,
    usuarioid integer NOT NULL,
    entrada timestamp without time zone NOT NULL,
    salida timestamp without time zone
);


ALTER TABLE public.registro OWNER TO postgres;

--
-- Name: registro_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.registro_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.registro_id_seq OWNER TO postgres;

--
-- Name: registro_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.registro_id_seq OWNED BY public.registro.id;


--
-- Name: usuarios; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.usuarios (
    numid integer NOT NULL,
    nombre character varying NOT NULL,
    apellidos character varying NOT NULL,
    admin integer DEFAULT 0 NOT NULL
);


ALTER TABLE public.usuarios OWNER TO postgres;

--
-- Name: registro id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.registro ALTER COLUMN id SET DEFAULT nextval('public.registro_id_seq'::regclass);


--
-- Data for Name: registro; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.registro (id, usuarioid, entrada, salida) FROM stdin;
61	22	2020-03-01 20:18:48	2020-03-01 20:18:57
62	12345	2020-03-01 20:19:03	2020-03-01 20:19:08
64	12345	2020-03-01 20:19:23	2020-03-01 20:19:28
65	22	2020-03-01 20:19:49	\N
63	0	2020-03-01 20:19:16	2020-03-02 09:24:48
66	0	2020-03-02 09:25:10	\N
67	1	2020-03-02 09:26:23	2020-03-02 09:26:27
68	1	2020-03-02 09:26:48	\N
\.


--
-- Data for Name: usuarios; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.usuarios (numid, nombre, apellidos, admin) FROM stdin;
0	Administrador	 	1
12345	Samuel	Serrano	1
22	Sam	Serrano	0
1	sam	martinez	0
\.


--
-- Name: registro_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.registro_id_seq', 68, true);


--
-- Name: registro registro_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.registro
    ADD CONSTRAINT registro_pkey PRIMARY KEY (id);


--
-- Name: usuarios usuarios_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.usuarios
    ADD CONSTRAINT usuarios_pkey PRIMARY KEY (numid);


--
-- Name: registro registro_usuarioid_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.registro
    ADD CONSTRAINT registro_usuarioid_fkey FOREIGN KEY (usuarioid) REFERENCES public.usuarios(numid) ON UPDATE CASCADE;


--
-- PostgreSQL database dump complete
--

